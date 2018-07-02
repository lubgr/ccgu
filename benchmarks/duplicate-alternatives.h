#ifndef DUPLICATE_ALTERNATIVES_H
#define DUPLICATE_ALTERNATIVES_H

#include <list>

namespace detail {
    template<class Container> class Gen {
        public:
            Gen(Container vOrig, unsigned nCopies) : v(std::move(vOrig)), nCopies(nCopies)
        {
            using std::begin;

            current = begin(v);
        }

            auto operator()()
            {
                if (++counter == nCopies) {
                    counter = 0;
                    return *current++;
                }

                return *current;
            }

        private:
            Container v;
            unsigned nCopies;
            unsigned counter = 0;
            typename Container::iterator current;
    };
}

template<class Container> void duplicateAlternative1(Container& v, unsigned n)
{
    detail::Gen<Container> gen(v, n);
    using std::begin;
    using std::end;

    v.resize(n*v.size());

    std::generate(begin(v), end(v), gen);
}

namespace detail {
    template<class Container> void duplicateAlternative2(Container& c, Container& result, unsigned n)
    {
        using std::cend;

        for (const auto& i: c)
            result.insert(cend(result), n, i);

        c = std::move(result);
    }
}

template<class T> void duplicateAlternative2(std::list<T>& v, unsigned n)
{
    std::list<T> result;

    detail::duplicateAlternative2(v, result, n);
}

template<class T> void duplicateAlternative2(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    detail::duplicateAlternative2(v, result, n);
}

#endif

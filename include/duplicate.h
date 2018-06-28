#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <algorithm>
#include <vector>
#include <list>

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

template<class Container> void duplicateInPlace1(Container& v, unsigned n)
{
    Gen<Container> gen(v, n);
    using std::begin;
    using std::end;

    v.resize(n*v.size());

    std::generate(begin(v), end(v), gen);
}

namespace detail {
    template<class Container> void duplicateInPlace2(Container& c, Container& result, unsigned n)
    {
        using std::cend;

        for (const auto& i: c)
            result.insert(cend(result), n, i);

        c = std::move(result);
    }
}

template<class T> void duplicateInPlace2(std::list<T>& v, unsigned n)
{
    std::list<T> result;

    detail::duplicateInPlace2(v, result, n);
}

template<class T> void duplicateInPlace2(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    detail::duplicateInPlace2(v, result, n);
}

template<class T> void duplicateInPlace3(std::vector<T>& v, unsigned n)
{
    using difference_type = typename std::vector<T>::difference_type;
    const auto origSize = static_cast<difference_type>(v.size());

    v.reserve(n*v.size());

    for (auto i = 0u; i < n - 1u; ++i) {
        const auto origEnd = begin(v) + origSize;

        v.insert(cend(v), begin(v), origEnd);
    }

    std::sort(begin(v), end(v));
}

template<class T> void duplicateInPlace3(std::list<T>& l, unsigned n)
{
    const auto origBegin = begin(l);
    using difference_type = typename std::list<T>::difference_type;
    const auto origSize = static_cast<difference_type>(l.size());

    l.insert(cend(l), origBegin, end(l));

    if (n == 1u)
        return;

    auto origEnd = origBegin;

    std::advance(origEnd, origSize);

    for (auto i = 0u; i < n - 2u; ++i)
        l.insert(cend(l), origBegin, origEnd);

    l.sort();
}

namespace detail {
    template<class Container> void duplicateInPlace4(Container& c, Container& result, unsigned n)
    {
        using std::begin;
        using std::end;
        unsigned insCount = n;

        for (auto i = begin(c); i != end(c); ++i) {
            auto next = i;

            if (++next != end(c)  && *next == *i) {
                insCount += n;
                continue;
            }

            result.insert(cend(result), insCount, *i);
            insCount = n;
        }

        c = std::move(result);
    }
}

template<class T> void duplicateInPlace4(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    detail::duplicateInPlace4(v, result, n);
}

template<class T> void duplicateInPlace4(std::list<T>& l, unsigned n)
{
    std::list<T> result;

    detail::duplicateInPlace4(l, result, n);
}

#endif

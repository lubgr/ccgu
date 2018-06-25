#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <algorithm>
#include <vector>

template<class Container> class Gen {
    public:
        Gen(Container vOrig, unsigned nCopies) : v(std::move(vOrig)), nCopies(nCopies)
    {
        current = std::begin(v);
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

template<class T> void duplicateInPlace1(std::vector<T>& v, unsigned n)
{
    Gen<std::vector<T>> gen(v, n);

    v.resize(n*v.size());

    std::generate(std::begin(v), std::end(v), gen);
}

template<class T> void duplicateInPlace2(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    for (const auto& i: v)
        result.insert(std::cend(result), n, i);

    v = std::move(result);
}

template<class T> void duplicateInPlace3(std::vector<T>& v, unsigned n)
{
    const auto origSize = v.size();

    v.reserve(n*v.size());

    for (unsigned i = 0; i < n - 1; ++i) {
        const auto origEnd = std::begin(v) + origSize;

        v.insert(std::end(v), std::begin(v), origEnd);
    }

    std::sort(std::begin(v), std::end(v));
}

#endif

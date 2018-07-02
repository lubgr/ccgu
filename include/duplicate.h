#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <vector>

namespace detail {
    template<class Container> void duplicate(Container& c, Container& result, unsigned n)
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

template<class T> void duplicate(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    detail::duplicate(v, result, n);
}

template<class Container> void duplicate(Container& c, unsigned n)
{
    Container result;

    detail::duplicate(c, result, n);
}

#endif

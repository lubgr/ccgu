#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <type_traits>
#include <vector>

namespace detail {
    template<class Container>
        void duplicate(Container& c, Container&& result, unsigned n, std::true_type)
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

    template<class Container>
        void duplicate(Container& c, Container&& result, unsigned n, std::false_type)
        {
            using std::cend;

            for (const auto& i: c)
                result.insert(cend(result), n, i);

            c = std::move(result);
        }

    template<class T, class = void>
        struct EqualityComparable
        : std::false_type{};

    template<class...> using void_t = void;

    template<class T>
        struct EqualityComparable<T, void_t<decltype(std::declval<T&>() == std::declval<T&>())>>
        : std::true_type{};

    template<class Container>
        void duplicate(Container& c, Container&& result, unsigned n)
        {
            using std::begin;
            EqualityComparable<decltype(*begin(c))> tag{};

            duplicate(c, std::move(result), n, tag);
        }
}

    template<class T>
void duplicate(std::vector<T>& v, unsigned n)
{
    std::vector<T> result;

    result.reserve(n*v.size());

    detail::duplicate(v, std::move(result), n);
}

    template<class Container>
void duplicate(Container& c, unsigned n)
{
    Container result;

    detail::duplicate(c, std::move(result), n);
}

#endif

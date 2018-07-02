#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <chrono>

template<class Fct, class Container> auto measure(Fct&& f, Container& c, unsigned n)
{
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    const auto before = clock::now();

    f(c, n);

    const auto duration = std::chrono::duration_cast<ms>(clock::now() - before);

    return duration.count();
}

#endif

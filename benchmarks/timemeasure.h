#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <chrono>
#include <iostream>

template<class Fct, class Container> void measure(const std::string& id, Fct&& f, Container& c, unsigned n)
{
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    const auto before = clock::now();

    f(c, n);

    const auto duration = std::chrono::duration_cast<ms>(clock::now() - before);

    std::cout << id << ": " << duration.count()/1000.0 << "ms" << std::endl;
}

#endif

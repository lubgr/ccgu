
#include <chrono>
#include <iostream>
#include <cassert>
#include <boost/lexical_cast.hpp>
#include "duplicate.h"

template<class Fct, class Container> void measure(Fct&& f, Container& c, unsigned n)
{
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    const auto before = clock::now();

    f(c, n);

    const auto duration = std::chrono::duration_cast<ms>(clock::now() - before);

    std::cout << "Duration " << duration.count()/1000.0 << "ms" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "[number-of-identical-elements]" << std::endl;

        exit(1);
    }

    const auto nIdenticalElements = boost::lexical_cast<unsigned>(argv[1]);
    const unsigned origSize = 10'000;
    const auto nGroups = 10;
    const auto n = 2;

    std::vector<int> vec(nGroups*nIdenticalElements);
    int value = 0;

    for (unsigned i = 0; i < nGroups; ++i) {
        ++value;

        std::fill(begin(vec) + i*nIdenticalElements, begin(vec) + i*nIdenticalElements + nIdenticalElements, value);
    }

    const auto orig = vec;

    measure(duplicateInPlace1<int>, vec, n);

    vec = orig;
    measure(duplicateInPlace2<int>, vec, n);

    vec = orig;
    measure(duplicateInPlace3<int>, vec, n);

    // vec = orig;
    // measure(duplicateInPlace4<int>, vec, n);

    return 0;
}

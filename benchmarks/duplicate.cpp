
#include <cassert>
#include "timemeasure.h"
#include <boost/lexical_cast.hpp>
#include "duplicate.h"

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

    measure("version 1", duplicateInPlace1<vec::value_type>, vec, n);

    vec = orig;
    measure("version 2", duplicateInPlace2<vec::value_type>, vec, n);

    vec = orig;
    measure("version 3", duplicateInPlace3<vec::value_type>, vec, n);

    vec = orig;
    measure("version 4", duplicateInPlace4<vec::value_type>, vec, n);

    return 0;
}

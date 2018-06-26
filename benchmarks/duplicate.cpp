
#include <cassert>
#include <cstdio>
#include "timemeasure.h"
#include "duplicate.h"

void logResult(int id, double ms, unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    std::printf("[%u-%u-%u] version %d: %.3f ms\n", nDuplicates, nGroups, nGroupLengths, id, ms);
}

template<class Container> void measureSample(unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    Container vec;
    using std::end;
    using std::begin;
    int value = 0;

    for (auto i = 0; i < static_cast<int>(nGroups); ++i)
        vec.insert(cend(vec), nGroupLengths, i + 1);

    const auto orig = vec;

    auto ms = measure<void(Container&, unsigned), Container>(duplicateInPlace1, vec, nDuplicates);
    logResult(1, ms, nDuplicates, nGroups, nGroupLengths);

    vec = orig;
    ms = measure<void(Container&, unsigned), Container>(duplicateInPlace2, vec, nDuplicates);
    logResult(2, ms, nDuplicates, nGroups, nGroupLengths);

    vec = orig;
    ms = measure<void(Container&, unsigned), Container>(duplicateInPlace3, vec, nDuplicates);
    logResult(3, ms, nDuplicates, nGroups, nGroupLengths);

    std::printf("\n");
}

int main(int, char**)
{
    const std::vector<unsigned> sizes = {1, 2, 5, 10, 100, 1'000, 10'000, 100'000, 1'000'000};
    static const unsigned finalSize = 100'000'000;

    for (const auto& nDuplicates : sizes)
        for (const auto& nGroups : sizes)
            for (const auto& nGroupLength : sizes)
                if (nDuplicates == 1)
                    continue;
                else if (nDuplicates*nGroups*nGroupLength == finalSize) {
                    std::printf("std::vector<int>\n\n");
                    measureSample<std::vector<int>>(nDuplicates, nGroups, nGroupLength);
                    std::printf("std::list<int>\n\n");
                    measureSample<std::list<int>>(nDuplicates, nGroups, nGroupLength);
                }

    return 0;
}

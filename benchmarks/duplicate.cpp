
#include <cassert>
#include <cstdio>
#include "timemeasure.h"
#include "duplicate.h"

void logResult(int id, double ms, unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    std::printf("[%u-%u-%u] version %d: %.3f ms\n", nDuplicates, nGroups, nGroupLengths, id, ms);
}

void measureSample(unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    std::vector<int> vec;
    using std::end;
    using std::begin;
    int value = 0;

    for (auto i = 0; i < static_cast<int>(nGroups); ++i)
        vec.insert(cend(vec), nGroupLengths, i + 1);

    const auto orig = vec;

    auto ms = measure(duplicateInPlace1<int>, vec, nDuplicates);
    logResult(1, ms, nDuplicates, nGroups, nGroupLengths);

    vec = orig;
    ms = measure(duplicateInPlace2<int>, vec, nDuplicates);
    logResult(2, ms, nDuplicates, nGroups, nGroupLengths);

    vec = orig;
    ms = measure(duplicateInPlace3<int>, vec, nDuplicates);
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
                else if (nDuplicates*nGroups*nGroupLength == finalSize)
                    measureSample(nDuplicates, nGroups, nGroupLength);

    return 0;
}

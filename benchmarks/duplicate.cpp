
#include <cassert>
#include <cstdio>
#include "timemeasure.h"
#include "duplicate.h"
#include "duplicate-alternatives.h"

void logResult(int id, long ms, unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    std::printf("[%u-%u-%u] version %d: %li ms\n", nDuplicates, nGroups, nGroupLengths, id, ms);
}

template<class Container> void measureSample(unsigned nDuplicates, unsigned nGroups, unsigned nGroupLengths)
{
    Container input;
    using std::end;
    using std::begin;

    for (auto i = 0; i < static_cast<int>(nGroups); ++i)
        input.insert(cend(input), nGroupLengths, i + 1);

    const auto orig = input;

    auto vec = orig;
    auto ms = measure<void(Container&, unsigned), Container>(duplicate, vec, nDuplicates);
    logResult(1, ms, nDuplicates, nGroups, nGroupLengths);

    auto vec1 = orig;
    ms = measure<void(Container&, unsigned), Container>(duplicateAlternative1, vec1, nDuplicates);
    logResult(2, ms, nDuplicates, nGroups, nGroupLengths);

    auto vec2 = orig;
    ms = measure<void(Container&, unsigned), Container>(duplicateAlternative2, vec2, nDuplicates);
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
                }

    return 0;
}

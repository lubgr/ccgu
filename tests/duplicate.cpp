
#include <list>
#include <deque>
#include <memory>
#include <catch2/catch.hpp>
#include "duplicate.h"

TEST_CASE("testDuplicateVector5x2")
{
    std::vector<int> ints{1, 3, 5, 5, 6};
    const std::vector<int> expected{1, 1, 3, 3, 5, 5, 5, 5, 6, 6};

    duplicate(ints, 2);

    REQUIRE(expected == ints);
}

TEST_CASE("testDuplicateVector3x3")
{
    std::vector<int> ints{2, 4, 7};
    const std::vector<int> expected{2, 2, 2, 4, 4, 4, 7, 7, 7};

    duplicate(ints, 3);

    REQUIRE(expected == ints);
}

TEST_CASE("testDuplicateVector2x5")
{
    std::vector<int> ints{1, 2};
    const std::vector<int> expected{1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

    duplicate(ints, 5);

    REQUIRE(expected == ints);
}

TEST_CASE("testDuplicateList5x3")
{
    std::list<int> ints{1, 1, 4, 5, 8};
    const std::list<int> expected{1, 1, 1, 1, 1, 1, 4, 4, 4, 5, 5, 5, 8, 8, 8};

    duplicate(ints, 3);

    REQUIRE(expected == ints);
}

TEST_CASE("testDuplicateList6x4")
{
    std::list<int> ints{0, 1, 2, 3, 4};
    const std::list<int> expected{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    duplicate(ints, 4);

    REQUIRE(expected == ints);
}

TEST_CASE("testDuplicateDeque3x1")
{
    std::deque<int> ints{1, 10, 100};
    const auto expected = ints;

    duplicate(ints, 1);

    REQUIRE(expected == ints);
}

struct A { int i; };

bool operator == (const A& lhs, const A& rhs)
{
    return lhs.i == rhs.i;
}

TEST_CASE("testDuplicateDequeUnsorted5x3")
{
   std::deque<A> comparableStructs{{10}, {6}, {1}, {3}, {2}};
   const std::deque<A> expected{{10}, {10}, {10}, {6}, {6}, {6}, {1}, {1}, {1}, {3}, {3}, {3}, {2}, {2}, {2}};

   duplicate(comparableStructs, 3);

   REQUIRE(expected == comparableStructs);
}

struct B { int i; };

TEST_CASE("testDuplicateVectorUnsortedNonComparable2x2")
{
    std::vector<B> nonComparableStructs{{20}, {10}};
    std::vector<B> expected{{20}, {20}, {10}, {10}};

    duplicate(nonComparableStructs, 2);

    REQUIRE(expected.size() == nonComparableStructs.size());

    for (std::vector<B>::size_type i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i].i == nonComparableStructs[i].i);
    }
}

struct C { int i; };

bool operator == (C&& lhs, C&& rhs)
{
    return lhs.i == rhs.i;
}

TEST_CASE("testDuplicateDequeOnlyRvalueComparable6x2")
{
    std::deque<C> rvalueComparableStructs{{-10}, {-5}, {0}, {5}, {20}, {40}};
    std::deque<C> expected{{-10}, {-10}, {-5}, {-5}, {0}, {0}, {5}, {5}, {20}, {20}, {40}, {40}};

    duplicate(rvalueComparableStructs, 2);

    REQUIRE(expected.size() == rvalueComparableStructs.size());

    for (std::vector<B>::size_type i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i].i == rvalueComparableStructs[i].i);
    }
}

TEST_CASE("testZeroDuplicates")
{
    std::vector<unsigned> v{0, 1, 2};

    duplicate(v, 0);

    REQUIRE(v.empty());
}

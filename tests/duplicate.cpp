
#include <list>
#include <deque>
#include <memory>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "duplicate.h"


namespace {
    template<class Function, class Container>
        void invokeAndCheck(Function&& f, const Container& expected, Container container, unsigned n)
        {
            using std::cbegin;
            using std::cend;

            auto orig = container;

            f(orig, n);

            REQUIRE(expected == orig);
        }

    template<class Container>
        void test(const Container& expected, Container input, unsigned n)
        {
            invokeAndCheck<void(Container&, unsigned), Container>(duplicate, expected, input, n);
        }
}

TEST_CASE("testDuplicateVector5x2")
{
    std::vector<int> ints{1, 3, 5, 5, 6};
    std::vector<int> expected{1, 1, 3, 3, 5, 5, 5, 5, 6, 6};

    test(expected, ints, 2);
}

TEST_CASE("testDuplicateVector3x3")
{
    std::vector<int> ints{2, 4, 7};
    std::vector<int> expected{2, 2, 2, 4, 4, 4, 7, 7, 7};

    test(expected, ints, 3);
}

TEST_CASE("testDuplicateVector2x5")
{
    std::vector<int> ints{1, 2};
    std::vector<int> expected{1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

    test(expected, ints, 5);
}

TEST_CASE("testDuplicateList5x3")
{
    std::list<int> ints{1, 1, 4, 5, 8};
    std::list<int> expected{1, 1, 1, 1, 1, 1, 4, 4, 4, 5, 5, 5, 8, 8, 8};

    test(expected, ints, 3);
}

TEST_CASE("testDuplicateList6x4")
{
    std::list<int> ints{0, 1, 2, 3, 4};
    std::list<int> expected{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    test(expected, ints, 4);
}

TEST_CASE("testDuplicateDeque3x1")
{
    std::deque<int> ints{1, 10, 100};

    test(ints, ints, 1);
}

struct A { int i; };

bool operator == (const A& lhs, const A& rhs)
{
   return lhs.i == rhs.i;
}

TEST_CASE("testDuplicateDequeUnsorted5x3")
{
   std::deque<A> input{{10}, {6}, {1}, {3}, {2}};
   std::deque<A> expected{{10}, {10}, {10}, {6}, {6}, {6}, {1}, {1}, {1}, {3}, {3}, {3}, {2}, {2}, {2}};

   test(expected, input, 3);
}

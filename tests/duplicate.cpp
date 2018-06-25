
#define BOOST_TEST_MODULE duplicate
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include "duplicate.h"

namespace {
    template<class Function, class Container>
        void invokeAndCheck(Function&& f, const Container& expected, Container container, unsigned n)
        {
            using std::cbegin;
            using std::cend;

            auto orig = container;

            f(orig, n);

            BOOST_CHECK_EQUAL_COLLECTIONS(cbegin(expected), cend(expected), cbegin(orig), cend(orig));
        }

    template<class Container>
        void test(const Container& expected, Container input, unsigned n)
        {
            using value_type = typename Container::value_type;

            invokeAndCheck(duplicateInPlace1<value_type>, expected, input, n);
            invokeAndCheck(duplicateInPlace2<value_type>, expected, input, n);
            invokeAndCheck(duplicateInPlace3<value_type>, expected, input, n);
            invokeAndCheck(duplicateInPlace4<value_type>, expected, input, n);
        }
}

BOOST_AUTO_TEST_CASE(testDuplicateInPlace2)
{
    std::vector<int> ints{1, 3, 5, 5, 6};
    std::vector<int> expected{1, 1, 3, 3, 5, 5, 5, 5, 6, 6};

    test(expected, ints, 2);
}

BOOST_AUTO_TEST_CASE(testDuplicateInPlace3)
{
    std::vector<int> ints{2, 4, 7};
    std::vector<int> expected{2, 2, 2, 4, 4, 4, 7, 7, 7};

    test(expected, ints, 3);
}

BOOST_AUTO_TEST_CASE(testDuplicateInPlace5)
{
    std::vector<int> ints{1, 2};
    std::vector<int> expected{1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

    test(expected, ints, 5);
}


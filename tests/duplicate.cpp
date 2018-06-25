
#define BOOST_TEST_MODULE duplicate
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include "duplicate.h"

namespace {
    template<class Function, class T> void invokeAndCheck(Function&& f, const T& expected, T container, unsigned n)
    {
        using std::cbegin;
        using std::cend;

        auto orig = container;

        f(orig, n);

        BOOST_CHECK_EQUAL_COLLECTIONS(cbegin(expected), cend(expected), cbegin(orig), cend(orig));
    }

    template<template<class, class> class Container, class T, class Alloc>
        void test(const Container<T, Alloc>& expected, Container<T, Alloc> input, unsigned n)
        {
            invokeAndCheck(duplicateInPlace1<T>, expected, input, n);
            invokeAndCheck(duplicateInPlace2<T>, expected, input, n);
            invokeAndCheck(duplicateInPlace3<T>, expected, input, n);
            invokeAndCheck(duplicateInPlace4<T>, expected, input, n);
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


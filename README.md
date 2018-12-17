
# Cohesionless collection of generic utilities [![Build Status](https://travis-ci.org/lubgr/ccgu.svg)](https://travis-ci.org/lubgr/ccgu) [![Build status](https://ci.appveyor.com/api/projects/status/lt7xtpfwm9x1ns5h?svg=true)](https://ci.appveyor.com/project/lubgr/ccgu)

This is a small gathering place for utility functions that were worth generalizing. Each utility is
kept in one header file in the `include` directory. Benchmarks and unit tests (using
[catch2](https://github.com/catchorg/Catch2)) are configured with [cmake](https://cmake.org), but
this is for testing only - actually using the snippets can be done by copying the desired header
file or its content. The template might work with pre-C++17, but this isn't tested.

transformOpt
------------

Filtering _and_ transforming sequences without using a range library is often implemented as two
separate steps in a handcrafted loop, as there is no algorithm in the standard library that combines
both steps. There is a `std::transform`-extension called `transform_if` in
[Boost](https://www.boost.org/doc/libs/1_67_0/libs/compute/doc/html/boost/compute/transform_if.html)
that takes an additional predicate argument to filter the elements before their transformation. But
as C++17 ships with `std::optional` and will be followed by `std::expected`, there is another way:
The function template `transformOpt` combines filter predicate and transformation operation into one
callable object. As the name of the algorithm suggests, the return value could be a `std::optional`
instance:
```c++
#include <vector>
#include <optional>
#include <numeric>
#include "transformopt.h"

std::vector<int> input(50);
std::vector<double> result;

std::iota(input.begin(), input.end(), 1);

transformOpt(input, std::back_inserter(result),
      [](int arg){ return arg % 10 == 0 ? std::optional<double>(arg + 3.14) : std::nullopt; });

// result is now {13.14, 23.14, 33.14, 43.14, 53.14}
```
In general, the callable can return any type that is convertible to `bool` and if this evaluates to
`true`, is also dereferencable. This includes other `optional` implementations, Boost outcome types,
`std::expected`, non-null raw pointers or smart pointer. When returning pointers from the callable,
note that the result of derefencing the return value is assigned to the output iterator. If the
pointer itself shall be inserted, it can be wrapped as e.g. `std::optional<int*>`.

duplicate
---------

This function template takes a standard sequence container (e.g. vector, deque, list) and an
`unsigned` argument `n` and duplicates the values in the input container such that there are `n`
entries per origionally element passed in, while the ordering is preserved. Example:
```c++
#include <vector>
#include "duplicate.h"

std::vector v{1, 2, 4, 10, 7};

duplicate(v, 3);

/* v is now {1, 1, 1, 2, 2, 2, 4, 4, 4, 10, 10, 10, 7, 7, 7} */
```
The resulting size is hence the original input size times `n`. The amount of calls to
`<container>::insert` is minimized when the container's `value_type` is equality comparable and has
equal adjacent elements (because it's sorted or by accident), otherwise there will be as many calls
to `insert` as elements in the original container passed in. For `std::vector` arguments,
`std::vector::reserve` is invoked before the insertions.

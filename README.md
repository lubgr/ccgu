
# Cohesionless collection of generic utilities [![Build Status](https://travis-ci.org/lubgr/ccgu.svg)](https://travis-ci.org/lubgr/ccgu) [![Build status](https://ci.appveyor.com/api/projects/status/lt7xtpfwm9x1ns5h?svg=true)](https://ci.appveyor.com/project/lubgr/ccgu)

This is a small gathering place for utility functions that were worth generalizing. Each utility is
kept in one header file in the `include` directory. Benchmarks and unit tests (using
[catch2](https://github.com/catchorg/Catch2)) are configured with [cmake](https://cmake.org), but
this is for testing only - actually using the snippets can be done by copying the desired header
file or its content.

duplicate
---------

This function takes a standard sequence container (e.g. vector, deque, list) and an `unsigned`
argument `n` and duplicates the values in the input container such that there are `n` entries per
origionally element passed in, while the ordering is preserved. Example:
```c++
#include <vector>
#include "duplicate.h"

std::vector<int> v{1, 2, 4, 10, 7};

duplicate(v, 3);

/* v is now {1, 1, 1, 2, 2, 2, 4, 4, 4, 10, 10, 10, 7, 7, 7} */
```
The resulting size is hence the original input size times `n`. The amount of calls to
`<container>::insert` is minimized when the container's `value_type` is equality comparable and has
equal adjacent elements (because it's sorted or by accident), otherwise there will be as many calls
to `insert` as elements in the original container passed in. For `std::vector` arguments,
`std::vector::reserve` is invoked before the insertions.

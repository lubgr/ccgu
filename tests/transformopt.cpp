
#include <catch2/catch.hpp>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <optional>
#include "transformopt.h"

template <int N> std::optional<std::string> toStringIfDividableBy(int arg)
{
   if (arg % N == 0)
      return std::to_string(arg);

   return std::nullopt;
}

TEST_CASE("Optionally transform number sequence")
{
   std::vector<int> input(50);
   std::iota(input.begin(), input.end(), 1);

   SECTION("To string when dividable by constant via function pointer")
   {
      std::vector<std::string> result;

      transformOpt(input, std::back_inserter(result), toStringIfDividableBy<10>);

      REQUIRE(result == std::vector<std::string>{"10", "20", "30", "40", "50"});
   }

   SECTION("To string when dividable by constant via lambda")
   {
      std::vector<int> input(50);
      std::vector<double> result;

      std::iota(input.begin(), input.end(), 1);

      transformOpt(input, std::back_inserter(result),
            [](int arg){ return arg % 10 == 0 ? std::optional<double>(arg + 3.14) : std::nullopt; });

      REQUIRE(result == std::vector<double>{13.14, 23.14, 33.14, 43.14, 53.14});
   }

   SECTION("Floating point arithmetic when argument is in interval")
   {
      std::list<double> result;

      transformOpt(input, std::back_inserter(result),
            [](int arg){ return (arg > 20 && arg < 25) ? std::optional<double>(arg + 0.123) : std::nullopt;  });

      REQUIRE(result == std::list{21.123, 22.123, 23.123, 24.123});
   }
}

TEST_CASE("Optionally transform pointers with nullptr as non-success indicator")
{
   std::vector<int> input(10);
   std::vector<int> result;

   std::iota(input.begin(), input.end(), 42);

   transformOpt(input, std::back_inserter(result), [](const int& arg){ return arg >= 50 ? &arg : nullptr; });

   REQUIRE(result == std::vector{50, 51});
}

namespace {
   struct EvenToBool {
      int n;
      operator bool() const { return n % 2 == 0; }
      int operator *() const { return n; }
   };

   auto evenToBool(int arg)
   {
      return EvenToBool{arg};
   }
}

TEST_CASE("Optionally transform custom type with conversion to bool")
{
   std::vector<int> input(10);
   std::vector<int> result(input.size()/2);

   std::iota(input.rbegin(), input.rend(), -10);

   transformOpt(input, result.begin(), evenToBool);

   REQUIRE(result == std::vector{-2, -4, -6, -8, -10});

}

TEST_CASE("Empty range input")
{
   std::vector<int> empty;
   std::vector<int> out;

   const auto ret = transformOpt(empty, out.begin(), [](auto&&){ return std::optional<int>{}; });

   REQUIRE(ret == out.cend());
}

#ifndef TRANSFORM_OPT_H
#define TRANSFORM_OPT_H

template <class InputIt, class OutputIt, class Fct>
OutputIt transformOpt(InputIt first, InputIt last, OutputIt dest, Fct transform)
{
   while (first != last) {
      if (const auto&& transformResult = transform(*first))
         *dest++ = *transformResult;

      ++first;
   }

   return dest;
}

   template <class Rng, class OutputIt, class Fct>
OutputIt transformOpt(Rng&& range, OutputIt dest, Fct transform)
{
   using std::cbegin;
   using std::cend;

   return transformOpt(cbegin(range), cend(range), dest, transform);
}

#endif

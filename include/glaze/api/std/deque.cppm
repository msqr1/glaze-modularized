#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <deque>
export module glaze.api.std.deque;
import glaze.core.meta;
#else
#include <deque>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::deque<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::deque<">, name_v<T>, chars<">">>;
   };
}

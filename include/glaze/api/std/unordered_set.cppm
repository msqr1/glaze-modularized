#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <unordered_set>
export module glaze.api.std.unordered_set;
import glaze.core.meta;
#else
#include <unordered_set>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::unordered_set<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::unordered_set<">, name_v<T>, chars<">">>;
   };
}

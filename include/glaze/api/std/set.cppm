#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <set>
export module glaze.api.std.set;
import glaze.core.meta;
#else
#include <set>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::set<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::set<">, name_v<T>, chars<">">>;
   };
}

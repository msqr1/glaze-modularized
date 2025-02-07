#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <vector>
export module glaze.api.std.vector;
import glaze.core.meta;
#else
#include <vector>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::vector<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::vector<">, name_v<T>, chars<">">>;
   };
}

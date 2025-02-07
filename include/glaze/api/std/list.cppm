#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <list>
export module glaze.api.std.list;
import glaze.core.meta;
#else
#include <list>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::list<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::list<">, name_v<T>, chars<">">>;
   };
}

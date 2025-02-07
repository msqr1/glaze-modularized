#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <memory>
export module glaze.api.std.unique_ptr;
import glaze.core.meta;
#else
#include <memory>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::unique_ptr<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::unique_ptr<">, name_v<T>, chars<">">>;
   };
}

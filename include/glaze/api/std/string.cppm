#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <string>
#include <string_view>
export module glaze.api.std.string;
import glaze.core.meta;
#else
#include <string>
#include <string_view>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <>
   struct meta<std::string>
   {
      static constexpr std::string_view name = "std::string";
   };
}

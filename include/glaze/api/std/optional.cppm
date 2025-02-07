#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <optional>
export module glaze.api.std.optional;
import glaze.core.meta;
#else
#include <optional>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   struct meta<std::optional<T>>
   {
      static constexpr std::string_view name = join_v<chars<"std::optional<">, name_v<T>, chars<">">>;
   };
}

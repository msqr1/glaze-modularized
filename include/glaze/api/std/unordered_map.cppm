#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <unordered_map>
export module glaze.api.std.unordered_map;
import glaze.core.meta;
#else
#include <unordered_map>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class Key, class Mapped>
   struct meta<std::unordered_map<Key, Mapped>>
   {
      static constexpr std::string_view name =
         join_v<chars<"std::unordered_map<">, name_v<Key>, chars<",">, name_v<Mapped>, chars<">">>;
   };
}

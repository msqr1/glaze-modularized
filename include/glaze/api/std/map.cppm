#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <map>
export module glaze.api.std.map;
import glaze.core.meta;
#else
#include <map>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class Key, class Mapped>
   struct meta<std::map<Key, Mapped>>
   {
      static constexpr std::string_view name =
         join_v<chars<"std::map<">, name_v<Key>, chars<",">, name_v<Mapped>, chars<">">>;
   };
}

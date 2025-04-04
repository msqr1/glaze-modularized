// Glaze Library
// For the license information refer to glaze.hpp

#pragma once

#include <string_view>
#include <unordered_map>

#include "glaze/core/meta.hpp"
#include "glaze/util/string_literal.hpp"

namespace glz
{
   template <class Key, class Mapped>
   struct meta<std::unordered_map<Key, Mapped>>
   {
      static constexpr std::string_view name =
         join_v<chars<"std::unordered_map<">, name_v<Key>, chars<",">, name_v<Mapped>, chars<">">>;
   };
}

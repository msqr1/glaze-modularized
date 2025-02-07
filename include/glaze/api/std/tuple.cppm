#pragma once
#include "../../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <tuple>
export module glaze.api.std.tuple;
import glaze.core.meta;
#else
#include <tuple>
#include "glaze/core/meta.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class... T>
   struct meta<std::tuple<T...>>
   {
      static constexpr std::string_view name = []<size_t... I>(std::index_sequence<I...>) {
         return join_v<chars<"std::tuple<">,
                       ((I != sizeof...(T) - 1) ? join_v<name_v<T>, chars<",">> : join_v<name_v<T>>)..., chars<">">>;
      }(std::make_index_sequence<sizeof...(T)>{});
   };
}

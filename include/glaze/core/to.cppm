// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#ifdef CPP_MODULES
export module glaze.core.to;
import glaze.core.common;
import glaze.core.opts;
#else
#include "glaze/core/common.cppm"
#include "glaze/core/opts.cppm"
#endif




// Common behavior for `to` specializations, typically applies for all formats

namespace glz::detail
{
   template <uint32_t Format>
   struct to<Format, hidden>
   {
      template <auto Opts>
      static void op(auto&& value, auto&&...) noexcept
      {
         static_assert(false_v<decltype(value)>, "hidden type should not be written");
      }
   };

   template <uint32_t Format>
   struct to<Format, skip>
   {
      template <auto Opts>
      static void op(auto&& value, auto&&...) noexcept
      {
         static_assert(false_v<decltype(value)>, "skip type should not be written");
      }
   };

   template <uint32_t Format, filesystem_path T>
   struct to<Format, T>
   {
      template <auto Opts, class... Args>
      static void op(auto&& value, is_context auto&& ctx, Args&&... args)
      {
         to<Format, decltype(value.string())>::template op<Opts>(value.string(), ctx, std::forward<Args>(args)...);
      }
   };
}

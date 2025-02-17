// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#include <type_traits>
#ifdef CPP_MODULES
export module glaze.json.raw_string;
import glaze.core.opts;
import glaze.json.read;
import glaze.json.write;
#else
#include "glaze/core/opts.cppm"
#include "glaze/json/read.cppm"
#include "glaze/json/write.cppm"
#endif





namespace glz
{
   // do not decode/encode escaped characters for strings
   template <class T>
   struct raw_string_t
   {
      T& val;
   };

   // oposite of raw_string_t, turns off the option
   template <class T>
   struct escaped_t
   {
      T& val;
   };

   namespace detail
   {
      template <class T>
      struct from<JSON, raw_string_t<T>>
      {
         template <auto Opts>
         GLZ_ALWAYS_INLINE static void op(auto&& value, auto&&... args)
         {
            read<JSON>::op<opt_true<Opts, &opts::raw_string>>(value.val, args...);
         }
      };

      template <class T>
      struct to<JSON, raw_string_t<T>>
      {
         template <auto Opts>
         GLZ_ALWAYS_INLINE static void op(auto&& value, is_context auto&& ctx, auto&&... args)
         {
            using val_t = std::remove_cvref_t<decltype(value.val)>;
            to<JSON, val_t>::template op<opt_true<Opts, &opts::raw_string>>(value.val, ctx, args...);
         }
      };

      template <class T>
      struct from<JSON, escaped_t<T>>
      {
         template <auto Opts>
         GLZ_ALWAYS_INLINE static void op(auto&& value, auto&&... args)
         {
            read<JSON>::op<opt_false<Opts, &opts::raw_string>>(value.val, args...);
         }
      };

      template <class T>
      struct to<JSON, escaped_t<T>>
      {
         template <auto Opts>
         GLZ_ALWAYS_INLINE static void op(auto&& value, is_context auto&& ctx, auto&&... args)
         {
            using val_t = std::remove_cvref_t<decltype(value.val)>;
            to<JSON, val_t>::template op<opt_false<Opts, &opts::raw_string>>(value.val, ctx, args...);
         }
      };

      template <auto MemPtr>
      GLZ_ALWAYS_INLINE constexpr decltype(auto) raw_string_impl() noexcept
      {
         return [](auto&& val) { return raw_string_t<std::remove_reference_t<decltype(val.*MemPtr)>>{val.*MemPtr}; };
      }

      template <auto MemPtr>
      GLZ_ALWAYS_INLINE constexpr decltype(auto) escaped_impl() noexcept
      {
         return [](auto&& val) { return escaped_t<std::remove_reference_t<decltype(val.*MemPtr)>>{val.*MemPtr}; };
      }
   }

   template <auto MemPtr>
   constexpr auto raw_string = detail::raw_string_impl<MemPtr>();

   template <auto MemPtr>
   constexpr auto escaped = detail::escaped_impl<MemPtr>();
}

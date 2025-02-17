// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#ifdef CPP_MODULES
export module glaze.file.hostname_include;
import glaze.core.common;
#else
#include "glaze/core/common.cppm"
#endif



#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#else
#endif


namespace glz
{
   namespace detail
   {
      template <class T>
      struct hostname_includer
      {
         T& value;

         static constexpr auto glaze_includer = true;
         static constexpr auto glaze_reflect = false;
      };
   }

   template <class T>
   struct meta<detail::hostname_includer<T>>
   {
      static constexpr std::string_view name = join_v<chars<"hostname_includer<">, name_v<T>, chars<">">>;
   };

   // Register this with an object to allow file including based on the hostname
   // This is useful for configuration files that should be specific to a host
   struct hostname_include final
   {
      bool reflection_helper{}; // needed for count_members
      static constexpr auto glaze_includer = true;
      static constexpr auto glaze_reflect = false;

      constexpr decltype(auto) operator()(auto&& value) const noexcept
      {
         using V = decay_keep_volatile_t<decltype(value)>;
         return detail::hostname_includer<V>{value};
      }
   };

   namespace detail
   {
      inline void replace_first_braces(std::string& original, const std::string& replacement) noexcept
      {
         static constexpr std::string_view braces = "{}";

         if (size_t pos = original.find(braces); pos != std::string::npos) {
            original.replace(pos, braces.size(), replacement);
         }
      }

      inline std::string get_hostname(context& ctx)
      {
         char hostname[256]{};

#ifdef _WIN32
         WSADATA wsaData;
         if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            ctx.error = error_code::hostname_failure;
            return {};
         }
#endif

         if (gethostname(hostname, sizeof(hostname))) {
            ctx.error = error_code::hostname_failure;
            return {};
         }

#ifdef _WIN32
         WSACleanup();
#endif

         return {hostname};
      }

      template <class T>
      struct from<JSON, hostname_includer<T>>
      {
         template <auto Options>
         static void op(auto&& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            constexpr auto Opts = ws_handled_off<Options>();
            std::string buffer{};
            read<JSON>::op<Opts>(buffer, ctx, it, end);
            if (bool(ctx.error)) [[unlikely]]
               return;

            replace_first_braces(buffer, get_hostname(ctx));
            if (bool(ctx.error)) [[unlikely]]
               return;

            const auto file_path = relativize_if_not_absolute(std::filesystem::path(ctx.current_file).parent_path(),
                                                              std::filesystem::path{buffer});

            const auto string_file_path = file_path.string();
            const auto ec = file_to_buffer(buffer, string_file_path);

            if (bool(ec)) [[unlikely]] {
               ctx.error = error_code::includer_error;
               auto& error_msg = error_buffer();
               error_msg = "file failed to open: " + string_file_path;
               ctx.includer_error = error_msg;
               return;
            }

            const auto current_file = ctx.current_file;
            ctx.current_file = string_file_path;

            std::string nested_buffer = buffer;
            static constexpr auto NestedOpts = opt_true<disable_padding_on<Opts>(), &opts::null_terminated>;
            const auto ecode = glz::read<NestedOpts>(value.value, nested_buffer, ctx);
            if (bool(ctx.error)) [[unlikely]] {
               ctx.error = error_code::includer_error;
               auto& error_msg = error_buffer();
               error_msg = glz::format_error(ecode, nested_buffer);
               ctx.includer_error = error_msg;
               return;
            }

            ctx.current_file = current_file;
         }
      };

      template <class T>
      struct to<JSON, hostname_includer<T>>
      {
         template <auto Opts>
         static void op(auto&&...) noexcept
         {}
      };
   }
}

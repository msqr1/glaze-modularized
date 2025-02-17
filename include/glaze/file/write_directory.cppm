// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#include <filesystem>
#ifdef CPP_MODULES
export module glaze.file.write_directory;
import glaze.core.write;
import glaze.file.file_ops;
#else
#include "glaze/core/write.cppm"
#include "glaze/file/file_ops.cppm"
#endif





namespace glz
{
   [[nodiscard]] inline error_ctx buffers_to_directory(
      const std::unordered_map<std::filesystem::path, std::string>& buffers, const sv directory)
   {
      namespace fs = std::filesystem;
      if (not fs::exists(directory)) {
         fs::create_directory(directory);
      }

      for (auto& [path, content] : buffers) {
         return {buffer_to_file(content, path.string())};
      }

      return {};
   }

   template <opts Opts = opts{}, detail::writable_map_t T>
   [[nodiscard]] error_ctx write_directory(T&& value, const sv directory_path)
   {
      namespace fs = std::filesystem;
      if (not fs::exists(directory_path)) {
         fs::create_directory(directory_path);
      }

      for (auto& [path, content] : value) {
         using Path = std::decay_t<decltype(path)>;
         std::string buffer{};
         if constexpr (std::same_as<std::filesystem::path, Path>) {
            if (auto ec = glz::write_json(content, buffer)) {
               return ec;
            }
            if (auto ec = buffer_to_file(buffer, path.string()); bool(ec)) {
               return {ec};
            }
         }
         else {
            if (auto ec = buffer_to_file(content, path); bool(ec)) {
               return {ec};
            }
         }
      }

      return {};
   }
}

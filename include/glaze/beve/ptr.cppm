#pragma once
#include "../../Export.hpp"
#ifdef CPP_MODULES
module;
export module glaze.beve.ptr;
import glaze.beve.read;
import glaze.beve.write;
import glaze.core.ptr;
#else
#include "glaze/beve/read.cppm"
#include "glaze/beve/write.cppm"
#include "glaze/core/ptr.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp



namespace glz
{
   template <class T, class B>
   bool read_as_binary(T&& root_value, const sv json_ptr, B&& buffer)
   {
      return read_as<opts{.format = BEVE}>(std::forward<T>(root_value), json_ptr, buffer);
   }

   template <class T, class B>
   bool write_as_binary(T&& root_value, const sv json_ptr, B&& buffer)
   {
      return write_as<opts{.format = BEVE}>(std::forward<T>(root_value), json_ptr, buffer);
   }
}

#pragma once
#include "../../Export.hpp"
#ifdef CPP_MODULES
module;
#include <tuple>
export module glaze.util.tuple;
import glaze.reflection.get_name;
import glaze.tuplet.tuple;
import glaze.util.for_each;
import glaze.util.string_literal;
#else
#include <tuple>
#include "glaze/reflection/get_name.cppm"
#include "glaze/tuplet/tuple.cppm"
#include "glaze/util/for_each.cppm"
#include "glaze/util/string_literal.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp




namespace glz
{
   template <class T>
   concept is_std_tuple = is_specialization_v<T, std::tuple>;

   // TODO: This doesn't appear to be used. Should it be removed?
   template <class Type>
   concept is_schema_class = requires {
      requires std::is_class_v<Type>;
      requires Type::schema_attributes;
   };
}

// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#if __has_include(<Eigen/Core>)
#include <Eigen/Core>
#endif
#include <span>
#ifdef CPP_MODULES
export module glaze.ext.eigen;
import glaze.api.std.array;
import glaze.beve.read;
import glaze.beve.write;
import glaze.core.common;
import glaze.core.meta;
import glaze.json.json_ptr;
import glaze.json.read;
import glaze.json.write;
#else
#include "glaze/api/std/array.cppm"
#include "glaze/beve/read.cppm"
#include "glaze/beve/write.cppm"
#include "glaze/core/common.cppm"
#include "glaze/core/meta.cppm"
#include "glaze/json/json_ptr.cppm"
#include "glaze/json/read.cppm"
#include "glaze/json/write.cppm"
#endif



#if __has_include(<Eigen/Core>)
#else
#error "Eigen must be included to use glaze/ext/eigen.hpp"
#endif



namespace glz
{
   namespace detail
   {
      template <matrix_t T>
         requires(T::RowsAtCompileTime >= 0 && T::ColsAtCompileTime >= 0)
      struct from<BEVE, T>
      {
         template <auto Opts>
         static void op(auto& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            ++it;
            if (it >= end) [[unlikely]] {
               ctx.error = error_code::unexpected_end;
               return;
            }
            constexpr uint8_t layout = uint8_t(!T::IsRowMajor);
            if (uint8_t(*it) != layout) {
               ctx.error = error_code::syntax_error;
            }
            ++it;
            std::array<Eigen::Index, 2> extents;
            detail::read<BEVE>::op<Opts>(extents, ctx, it, end);

            std::span<typename T::Scalar, T::RowsAtCompileTime * T::ColsAtCompileTime> view(value.data(), value.size());
            detail::read<BEVE>::op<Opts>(view, ctx, it, end);
         }
      };

      // A dynamic matrix in both rows and columns
      template <matrix_t T>
         requires(T::RowsAtCompileTime < 0 && T::ColsAtCompileTime < 0)
      struct from<BEVE, T>
      {
         template <auto Opts>
         static void op(auto& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            ++it;
            if (it >= end) [[unlikely]] {
               ctx.error = error_code::unexpected_end;
               return;
            }
            constexpr uint8_t layout = uint8_t(!T::IsRowMajor);
            if (uint8_t(*it) != layout) {
               ctx.error = error_code::syntax_error;
               return;
            }
            ++it;
            std::array<Eigen::Index, 2> extents;
            detail::read<BEVE>::op<Opts>(extents, ctx, it, end);

            value.resize(extents[0], extents[1]);
            std::span<typename T::Scalar> view(value.data(), extents[0] * extents[1]);
            detail::read<BEVE>::op<Opts>(view, ctx, it, end);
         }
      };

      template <matrix_t T>
         requires(T::RowsAtCompileTime >= 0 && T::ColsAtCompileTime >= 0)
      struct to<BEVE, T>
      {
         template <auto Opts>
         static void op(auto&& value, is_context auto&& ctx, auto&&... args)
         {
            constexpr uint8_t matrix = 0b00010'000;
            constexpr uint8_t tag = tag::extensions | matrix;
            dump_type(tag, args...);

            constexpr uint8_t layout = uint8_t(!T::IsRowMajor);
            dump_type(layout, args...);

            std::array<Eigen::Index, 2> extents{T::RowsAtCompileTime, T::ColsAtCompileTime};
            detail::write<BEVE>::op<Opts>(extents, ctx, args...);

            std::span<typename T::Scalar, T::RowsAtCompileTime * T::ColsAtCompileTime> view(value.data(), value.size());
            detail::write<BEVE>::op<Opts>(view, ctx, args...);
         }
      };

      // A dynamic matrix in both rows and columns
      template <matrix_t T>
         requires(T::RowsAtCompileTime < 0 && T::ColsAtCompileTime < 0)
      struct to<BEVE, T>
      {
         template <auto Opts>
         static void op(auto&& value, is_context auto&& ctx, auto&&... args)
         {
            constexpr uint8_t matrix = 0b00010'000;
            constexpr uint8_t tag = tag::extensions | matrix;
            dump_type(tag, args...);

            constexpr uint8_t layout = uint8_t(!T::IsRowMajor);
            dump_type(layout, args...);

            std::array<Eigen::Index, 2> extents{value.rows(), value.cols()};
            detail::write<BEVE>::op<Opts>(extents, ctx, args...);

            std::span<typename T::Scalar> view(value.data(), extents[0] * extents[1]);
            detail::write<BEVE>::op<Opts>(view, ctx, args...);
         }
      };

      template <matrix_t T>
         requires(T::RowsAtCompileTime >= 0 && T::ColsAtCompileTime >= 0)
      struct from<JSON, T>
      {
         template <auto Opts>
         static void op(auto& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            std::span<typename T::Scalar, T::RowsAtCompileTime * T::ColsAtCompileTime> view(value.data(), value.size());
            detail::read<JSON>::op<Opts>(view, ctx, it, end);
         }
      };

      template <matrix_t T>
         requires(T::RowsAtCompileTime >= 0 && T::ColsAtCompileTime >= 0)
      struct to<JSON, T>
      {
         template <auto Opts>
         static void op(auto&& value, is_context auto&& ctx, auto&& b, auto&& ix)
         {
            std::span<typename T::Scalar, T::RowsAtCompileTime * T::ColsAtCompileTime> view(value.data(), value.size());
            using Value = std::remove_cvref_t<decltype(value)>;
            detail::to<JSON, Value>::template op<Opts>(view, ctx, b, ix);
         }
      };

      // A dynamic matrix in both rows and columns
      template <matrix_t T>
         requires(T::RowsAtCompileTime < 0 && T::ColsAtCompileTime < 0)
      struct to<JSON, T>
      {
         template <auto Opts>
         static void op(auto&& value, is_context auto&& ctx, auto&& b, auto&& ix)
         {
            dump<'['>(b, ix);
            using RowColT = std::array<Eigen::Index, 2>;
            RowColT extents{value.rows(), value.cols()};
            detail::to<JSON, RowColT>::template op<Opts>(extents, ctx, b, ix);
            dump<','>(b, ix);

            std::span<typename T::Scalar> view(value.data(), value.size());
            using Value = std::remove_cvref_t<decltype(view)>;
            detail::to<JSON, Value>::template op<Opts>(view, ctx, b, ix);
            dump<']'>(b, ix);
         }
      };

      // A dynamic matrix in both rows and columns
      template <matrix_t T>
         requires(T::RowsAtCompileTime < 0 && T::ColsAtCompileTime < 0)
      struct from<JSON, T>
      {
         template <auto Opts>
         static void op(auto& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            if (match_invalid_end<'[', Opts>(ctx, it, end)) {
               return;
            }
            std::array<Eigen::Index, 2> extents; // NOLINT
            detail::read<JSON>::op<Opts>(extents, ctx, it, end);
            value.resize(extents[0], extents[1]);
            if (*it == ',') {
               // we have data
               ++it;
               if constexpr (not Opts.null_terminated) {
                  if (it == end) [[unlikely]] {
                     ctx.error = error_code::unexpected_end;
                     return;
                  }
               }
               std::span<typename T::Scalar> view(value.data(), extents[0] * extents[1]);
               detail::read<JSON>::op<Opts>(view, ctx, it, end);
            }
            match<']'>(ctx, it);
         }
      };

      template <typename Scalar, int Dim, int Mode>
      struct from<JSON, Eigen::Transform<Scalar, Dim, Mode>>
      {
         template <auto Opts>
         static void op(auto& value, is_context auto&& ctx, auto&& it, auto&& end)
         {
            constexpr auto size =
               Mode == Eigen::TransformTraits::AffineCompact ? (Dim + 1) * Dim : (Dim + 1) * (Dim + 1);
            std::span<Scalar, size> view(value.data(), size);
            detail::read<JSON>::op<Opts>(view, ctx, it, end);
         }
      };

      template <typename Scalar, int Dim, int Mode>
      struct to<JSON, Eigen::Transform<Scalar, Dim, Mode>>
      {
         template <auto Opts>
         static void op(auto&& value, is_context auto&& ctx, auto&& b, auto&& ix)
         {
            constexpr auto size =
               Mode == Eigen::TransformTraits::AffineCompact ? (Dim + 1) * Dim : (Dim + 1) * (Dim + 1);
            std::span<Scalar, size> view(value.data(), size);
            using Value = std::remove_cvref_t<decltype(value)>;
            detail::to<JSON, Value>::template op<Opts>(view, ctx, b, ix);
         }
      };
   } // namespace detail
} // namespace glaze

template <class Scalar, int Rows, int Cols>
struct glz::meta<Eigen::Matrix<Scalar, Rows, Cols>>
{
   static constexpr std::string_view name = join_v<chars<"Eigen::Matrix<">, name_v<Scalar>, chars<",">, //
                                                   chars<num_to_string<Rows>::value>, chars<",">, //
                                                   chars<num_to_string<Cols>::value>, chars<",">, //
                                                   chars<">">>;
};

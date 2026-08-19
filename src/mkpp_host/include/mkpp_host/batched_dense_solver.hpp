#pragma once

#include <Kokkos_Core.hpp>
#include "dispatcher.hpp"

#ifdef MKPP_HAS_KOKKOS_KERNELS
#include <KokkosBatched_LU_Decl.hpp>
#include <KokkosBatched_Trsv_Decl.hpp>
#endif

namespace mkpp {
namespace host {

template <typename ErrorView>
KOKKOS_INLINE_FUNCTION void set_cell_error(const ErrorView& err, size_t cell_idx, CellErrorCode code) {
    if constexpr (requires { err.set_error(cell_idx, code); }) {
        err.set_error(cell_idx, code);
    } else {
        err(cell_idx) = static_cast<int>(code);
    }
}

/**
 * @brief Executes batched LU factorization and triangular solve for B independent N x N dense matrices.
 *
 * Uses KokkosBatched::SerialLU / SerialTrsv when KokkosKernels is enabled, or explicit
 * unblocked LU factorization and forward/backward substitution.
 *
 * @tparam TeamMember Kokkos TeamPolicy member type or execution handle
 * @tparam MatrixView 3D Kokkos View with shape [B, N, N] and LayoutLeft
 * @tparam VectorView 2D Kokkos View with shape [B, N] and LayoutLeft
 * @tparam ErrorView 1D Kokkos View with shape [B] storing integer error codes or BatchErrorStatus
 *
 * @param member Kokkos team member execution handle
 * @param A Batched system matrix [B, N, N] (overwritten with LU factors)
 * @param b Right-hand-side vector [B, N] (overwritten with solution x)
 * @param error_status Per-cell status flags [B]
 */
template <typename TeamMember, typename MatrixView, typename VectorView, typename ErrorView>
KOKKOS_INLINE_FUNCTION void batched_dense_solve(
    const TeamMember& member,
    const MatrixView& A,
    const VectorView& b,
    const ErrorView& error_status) {
    const int num_cells = static_cast<int>(A.extent(0));
    const int N = static_cast<int>(A.extent(1));

    const int team_rank = member.league_rank();
    const int num_teams = member.league_size();
    const int cells_per_team = (num_cells + num_teams - 1) / num_teams;
    const int begin_cell = team_rank * cells_per_team;
    const int end_cell = (begin_cell + cells_per_team < num_cells) ? (begin_cell + cells_per_team) : num_cells;

    Kokkos::parallel_for(Kokkos::TeamThreadRange(member, begin_cell, end_cell), [=](const int cell_idx) {
        auto A_sub = Kokkos::subview(A, cell_idx, Kokkos::ALL(), Kokkos::ALL());
        auto b_sub = Kokkos::subview(b, cell_idx, Kokkos::ALL());

        // Singular matrix check prior to / during LU
        bool is_singular = false;

#ifdef MKPP_HAS_KOKKOS_KERNELS
        // Check diagonal elements for zero / singular
        for (int k = 0; k < N; ++k) {
            if (Kokkos::abs(A_sub(k, k)) < 1.0e-15) {
                is_singular = true;
                break;
            }
        }

        if (is_singular) {
            set_cell_error(error_status, cell_idx, ERR_SINGULAR_MATRIX);
            return;
        }

        // KokkosBatched LU Factorization
        int lu_err = KokkosBatched::SerialLU<KokkosBatched::Algo::LU::Unblocked>::invoke(A_sub);
        if (lu_err != 0) {
            set_cell_error(error_status, cell_idx, ERR_SINGULAR_MATRIX);
            return;
        }

        // KokkosBatched Lower Triangular Solve (L * y = b, unit diagonal)
        KokkosBatched::SerialTrsv<
            KokkosBatched::Uplo::Lower,
            KokkosBatched::Trans::NoTranspose,
            KokkosBatched::Diag::Unit,
            KokkosBatched::Algo::Trsv::Unblocked>::invoke(1.0, A_sub, b_sub);

        // KokkosBatched Upper Triangular Solve (U * x = y, non-unit diagonal)
        KokkosBatched::SerialTrsv<
            KokkosBatched::Uplo::Upper,
            KokkosBatched::Trans::NoTranspose,
            KokkosBatched::Diag::NonUnit,
            KokkosBatched::Algo::Trsv::Unblocked>::invoke(1.0, A_sub, b_sub);
#else
        // Unblocked LU Factorization in-place (A = L * U)
        for (int k = 0; k < N; ++k) {
            double pivot = A_sub(k, k);
            if (Kokkos::abs(pivot) < 1.0e-15) {
                is_singular = true;
                break;
            }
            for (int i = k + 1; i < N; ++i) {
                A_sub(i, k) /= pivot;
                double mult = A_sub(i, k);
                for (int j = k + 1; j < N; ++j) {
                    A_sub(i, j) -= mult * A_sub(k, j);
                }
            }
        }

        if (is_singular) {
            set_cell_error(error_status, cell_idx, ERR_SINGULAR_MATRIX);
            return;
        }

        // Forward Substitution (L * y = b)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                b_sub(i) -= A_sub(i, j) * b_sub(j);
            }
        }

        // Backward Substitution (U * x = y)
        for (int i = N - 1; i >= 0; --i) {
            for (int j = i + 1; j < N; ++j) {
                b_sub(i) -= A_sub(i, j) * b_sub(j);
            }
            double diag = A_sub(i, i);
            if (Kokkos::abs(diag) < 1.0e-15) {
                set_cell_error(error_status, cell_idx, ERR_SINGULAR_MATRIX);
                return;
            }
            b_sub(i) /= diag;
        }
#endif
    });
}

}  // namespace host
}  // namespace mkpp

#pragma once

#include <cstddef>
#include <optional>
#include <vector>

namespace lab {

using Matrix = std::vector<std::vector<double>>;

enum class LoopOrder {
    IJK,
    IKJ,
    JIK,
    JKI,
    KIJ,
    KJI
};

std::optional<Matrix> create_random_matrix(std::size_t n);
Matrix multiply_matrices(const Matrix& A, const Matrix& B, LoopOrder order);
bool are_matrices_equal(const Matrix& A, const Matrix& B, double epsilon = 1e-9);

} // namespace lab
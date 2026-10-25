#include "matrix_ops.h"
#include <random>
#include <cmath>

namespace lab {

// Скрытая (вспомогательная) функция. Видна только внутри этого файла.
namespace {
    Matrix create_zero_matrix(std::size_t n) {
        return Matrix(n, std::vector<double>(n, 0.0));
    }
}

// 1. Создание матрицы
std::optional<Matrix> create_random_matrix(std::size_t n) {
    if (n == 0) return std::nullopt; // Проверка на дурака

    Matrix m = create_zero_matrix(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (auto& row : m) {
        for (auto& val : row) {
            val = dis(gen); // Заполняем случайными числами от 0 до 1
        }
    }
    return m;
}

// 2. ТО САМОЕ УМНОЖЕНИЕ МАТРИЦ
Matrix multiply_matrices(const Matrix& A, const Matrix& B, LoopOrder order) {
    if (A.empty() || B.empty() || A[0].empty() || B[0].empty()) {
        return {}; // Если матрицы пустые - возвращаем пустую
    }
    
    std::size_t n = A.size();
    // Проверяем, что матрицы квадратные и одинакового размера
    if (B.size() != n || A[0].size() != n || B[0].size() != n) {
        return {};
    }

    Matrix C = create_zero_matrix(n); // Сюда будем складывать результат

    // А вот и наши 6 порядков циклов!
    switch (order) {
        case LoopOrder::IJK:
            for (std::size_t i = 0; i < n; ++i)
                for (std::size_t j = 0; j < n; ++j)
                    for (std::size_t k = 0; k < n; ++k)
                        C[i][j] += A[i][k] * B[k][j];
            break;
            
        case LoopOrder::IKJ:
            for (std::size_t i = 0; i < n; ++i)
                for (std::size_t k = 0; k < n; ++k) {
                    double a = A[i][k]; // Сохраняем во временную переменную
                    for (std::size_t j = 0; j < n; ++j)
                        C[i][j] += a * B[k][j];
                }
            break;
            
        case LoopOrder::JIK:
            for (std::size_t j = 0; j < n; ++j)
                for (std::size_t i = 0; i < n; ++i)
                    for (std::size_t k = 0; k < n; ++k)
                        C[i][j] += A[i][k] * B[k][j];
            break;
            
        case LoopOrder::JKI:
            for (std::size_t j = 0; j < n; ++j)
                for (std::size_t k = 0; k < n; ++k) {
                    double b = B[k][j];
                    for (std::size_t i = 0; i < n; ++i)
                        C[i][j] += A[i][k] * b;
                }
            break;
            
        case LoopOrder::KIJ:
            for (std::size_t k = 0; k < n; ++k)
                for (std::size_t i = 0; i < n; ++i) {
                    double a = A[i][k];
                    for (std::size_t j = 0; j < n; ++j)
                        C[i][j] += a * B[k][j];
                }
            break;
            
        case LoopOrder::KJI:
            for (std::size_t k = 0; k < n; ++k)
                for (std::size_t j = 0; j < n; ++j) {
                    double b = B[k][j];
                    for (std::size_t i = 0; i < n; ++i)
                        C[i][j] += A[i][k] * b;
                }
            break;
    }
    return C;
}

// 3. Проверка равенства (нужна для тестов)
bool are_matrices_equal(const Matrix& A, const Matrix& B, double epsilon) {
    if (A.size() != B.size()) return false;
    for (std::size_t i = 0; i < A.size(); ++i) {
        if (A[i].size() != B[i].size()) return false;
        for (std::size_t j = 0; j < A[i].size(); ++j) {
            if (std::abs(A[i][j] - B[i][j]) > epsilon) return false;
        }
    }
    return true;
}

} // namespace lab
#include "benchmark.h"
#include <chrono>
#include <iostream>

namespace lab {

std::vector<double> run_benchmark_for_order(
    const std::vector<std::size_t>& sizes, 
    LoopOrder order
) {
    std::vector<double> times;
    times.reserve(sizes.size());

    for (auto n : sizes) {
        auto A = create_random_matrix(n);
        auto B = create_random_matrix(n);
        
        if (!A || !B) continue;

        // Засекаем время ДО умножения
        auto start = std::chrono::high_resolution_clock::now();
        Matrix C = multiply_matrices(*A, *B, order);
        // Засекаем время ПОСЛЕ
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> diff = end - start;
        times.push_back(diff.count()); // Сохраняем время в секундах
    }
    return times;
}

} // namespace lab
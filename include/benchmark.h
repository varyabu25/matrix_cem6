#pragma once

#include "matrix_ops.h"
#include <cstddef>
#include <vector>

namespace lab {

// Запуск замеров для одного порядка
std::vector<double> run_benchmark_for_order(
    const std::vector<std::size_t>& sizes, 
    LoopOrder order
);

} // namespace lab
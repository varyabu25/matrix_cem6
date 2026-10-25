#include "matrix_ops.h"
#include "benchmark.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void run_manual_tests() {
    std::cout << "--- Tests ---\n";
    
    auto A = lab::create_random_matrix(10);
    auto B = lab::create_random_matrix(10);
    if (A && B) {
        auto C1 = lab::multiply_matrices(*A, *B, lab::LoopOrder::IJK);
        auto C2 = lab::multiply_matrices(*A, *B, lab::LoopOrder::KJI);
        if (lab::are_matrices_equal(C1, C2)) {
            std::cout << "[PASS] Normal case\n";
        } else {
            std::cout << "[FAIL] Normal case\n";
        }
    }
    
    lab::Matrix empty_mat;
    auto empty_res = lab::multiply_matrices(empty_mat, empty_mat, lab::LoopOrder::IJK);
    if (empty_res.empty()) {
        std::cout << "[PASS] Empty matrix case\n";
    } else {
        std::cout << "[FAIL] Empty matrix case\n";
    }

    auto zero_mat = lab::create_random_matrix(0);
    if (!zero_mat.has_value()) {
        std::cout << "[PASS] Zero size case\n";
    } else {
        std::cout << "[FAIL] Zero size case\n";
    }
}

void run_benchmark() {
    std::vector<std::size_t> sizes;
    for (std::size_t i = 10; i <= 100; i += 30) sizes.push_back(i);
    for (std::size_t i = 150; i <= 300; i += 50) sizes.push_back(i);
    sizes.push_back(500);

    std::cout << "Order,Size,Time_sec\n";

    lab::LoopOrder orders[] = {
        lab::LoopOrder::IJK, lab::LoopOrder::IKJ, 
        lab::LoopOrder::JIK, lab::LoopOrder::JKI, 
        lab::LoopOrder::KIJ, lab::LoopOrder::KJI
    };
    
    const char* order_names[] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};

    for (std::size_t i = 0; i < 6; ++i) {
        std::cerr << "Running order: " << order_names[i] << "...\n";
        auto times = lab::run_benchmark_for_order(sizes, orders[i]);
        
        for (std::size_t j = 0; j < sizes.size(); ++j) {
            std::cout << order_names[i] << "," 
                      << sizes[j] << "," 
                      << std::fixed << std::setprecision(6) << times[j] << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage:\n  matrix_benchmark --test\n  matrix_benchmark --bench\n";
        return 0;
    }

    std::string arg = argv[1];
    if (arg == "--test") {
        run_manual_tests();
    } else if (arg == "--bench") {
        run_benchmark();
    }
    return 0;
}
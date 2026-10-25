cmake_minimum_required(VERSION 3.10)
project(MatrixBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(matrix_benchmark 
    src/main.cpp 
    src/matrix_ops.cpp 
    src/benchmark.cpp
)

# Вот эта строка говорит компилятору искать .h файлы в папке include
target_include_directories(matrix_benchmark PRIVATE include)
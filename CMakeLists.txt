cmake_minimum_required(VERSION 3.10)
add_compile_definitions(LIBTEST_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(a_plus_b a_plus_b/solution_sample.cpp)
target_link_libraries(a_plus_b pthread stdc++fs)

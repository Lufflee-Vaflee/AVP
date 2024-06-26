cmake_minimum_required(VERSION 3.5)
project(SIMD_TEST)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif ()

if (NOT CMAKE_COMPILER_IS_GNUCXX)
    #message( FATAL_ERROR "COMPILER IS NOT GNU_CXX, EXITING" )
endif ()


if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Config file
set(L3_SIZE 0)
set(L2_SIZE 0)
set(L1_SIZE 0)
set(MULTIPLIER 0.9)

execute_process (
    COMMAND bash -c "getconf LEVEL3_CACHE_SIZE"
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE L3_SIZE
)

execute_process (
    COMMAND bash -c "getconf LEVEL2_CACHE_SIZE"
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE L2_SIZE
)

execute_process (
    COMMAND bash -c "getconf LEVEL1_DCACHE_SIZE"
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE L1_SIZE
)

configure_file(config/Config.hpp.in Config.hpp)


add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME}  PUBLIC
    -O3
    #-fno-tree-vectorize
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${NoSIMD} 
    ${SIMD} 
    ${INTRINSICS}
)
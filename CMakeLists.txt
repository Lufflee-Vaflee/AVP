cmake_minimum_required(VERSION 3.5)
project(SIMD_TEST)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()

if (NOT CMAKE_COMPILER_IS_GNUCXX)
    message( FATAL_ERROR "COMPILER IS NOT GNU_CXX, EXETING" )
endif ()

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()


#INTRINSICS_LIB
set(INTRINSICS ${PROJECT_NAME}_INTRINSICS)

add_library(${INTRINSICS} STATIC Intrinsics/lib.cpp)

target_include_directories(${INTRINSICS} PRIVATE 
    Intrinsics
)

target_compile_options(${INTRINSICS} PRIVATE
    -O2
)


#NoSIMD_LIB
set(NoSIMD ${PROJECT_NAME}_NoSIMD)

add_library(${NoSIMD} STATIC NoSIMD/lib.cpp)

target_include_directories(${NoSIMD} PRIVATE 
    NoSIMD
)

target_compile_options(${NoSIMD} PRIVATE
    -O2
    -fno-tree-vectorize
)


#SIMD_LIB
set(SIMD ${PROJECT_NAME}_SIMD)

add_library(${SIMD} STATIC SIMD/lib.cpp)

target_include_directories(${SIMD} PRIVATE 
    SIMD
)

target_compile_options(${SIMD} PRIVATE
    -O2
)



add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -O2
)

target_include_directories(${PROJECT_NAME} PUBLIC
    /SIMD
    /NoSIMD
    /Intrinsics
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${NoSIMD} 
    ${SIMD} 
    ${INTRINSICS}
)
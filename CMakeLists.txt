cmake_minimum_required(VERSION 3.14)
project(ccq_qdags)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

include_directories(includes)
include_directories(external/sdsl-lite/include)
include_directories(external/sdsl-lite/build/external/libdivsufsort/include)
include_directories(src)

add_executable(j4_ghd queries/j4_ghd.cpp)

target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)


add_executable(j3_ghd queries/j3_ghd.cpp)

target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(ti4_ghd queries/ti4_ghd.cpp)

target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

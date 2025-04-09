cmake_minimum_required(VERSION 3.14)
project(ccq_qdags)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

include_directories(includes)
include_directories(external/sdsl-lite/include)
include_directories(external/sdsl-lite/build/external/libdivsufsort/include)
include_directories(src)

# add_executable(qdags queries/j3.cpp
    #queries/j4.cpp
    #queries/p2.cpp
    #queries/p3.cpp
    #queries/p4.cpp
    #queries/s1.cpp
    #queries/s2.cpp
    #queries/s3.cpp
    #queries/s4.cpp
    #queries/t2.cpp
    #queries/t4.cpp
    #queries/ti2.cpp
    #queries/ti3.cpp
    #queries/ti4.cpp
    #queries/tr1.cpp
    #queries/tr2.cpp
#   )
add_executable(triangle_tadpole includes/initArray.hpp queries/triangle_tadpole.cpp)

target_link_libraries(triangle_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(triangle_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(triangle_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(triangle_barbell includes/initArray.hpp queries/triangle_barbell.cpp)

target_link_libraries(triangle_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(triangle_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(triangle_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(j3_ghd includes/initArray.hpp queries/j3_ghd.cpp)

target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(j3_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(square_tadpole includes/initArray.hpp queries/square_tadpole.cpp)

target_link_libraries(square_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(square_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(square_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(penta_barbell includes/initArray.hpp queries/penta_barbell.cpp)

target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)


add_executable(ccq_qdags includes/initArray.hpp queries/ghd_test.cpp)

target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(j4_ghd includes/initArray.hpp queries/j4_ghd.cpp)

target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(j4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)


add_executable(ti4_ghd includes/initArray.hpp queries/ti4_ghd.cpp)

target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(ti4_ghd ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)


#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

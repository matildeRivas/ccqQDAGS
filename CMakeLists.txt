cmake_minimum_required(VERSION 3.14)
project(ccq_qdags)

set(CMAKE_CXX_STANDARD 14)


include_directories(includes)
include_directories(external/sdsl-lite/include)
include_directories(external/sdsl-lite/build/external/libdivsufsort/include)
include_directories(src)

add_executable(qdags queries/j3.cpp
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
        )
add_executable(ccq_qdags  queries/join_test.cpp) #src/test.cpp
add_executable(ex external/sdsl-lite/tutorial/expl-04.cpp)

target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(ccq_qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

target_link_libraries(ex ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)
target_link_libraries(ex ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(ex ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)


include_directories(includes)
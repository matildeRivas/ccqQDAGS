cmake_minimum_required(VERSION 3.14)
project(ccq_qdags)

set(CMAKE_CXX_STANDARD 14)


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
#add_executable(sq_tadpole includes/initArray.hpp queries/square_tadpole1.cpp)
#
#target_link_libraries(sq_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
#target_link_libraries(sq_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
#target_link_libraries(sq_tadpole ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_executable(tr_barbell includes/initArray.hpp queries/triangle_barbell.cpp)

target_link_libraries(tr_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
target_link_libraries(tr_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
target_link_libraries(tr_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

#add_executable(sq_barbell includes/initArray.hpp queries/square_barbell.cpp)

#target_link_libraries(sq_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
#target_link_libraries(sq_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
#target_link_libraries(sq_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

#add_executable(penta_barbell includes/initArray.hpp queries/penta_barbell.cpp)

#target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
#target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
#target_link_libraries(penta_barbell ${CMAKE_SOURCE_DIR}square_barbell.cpp/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)


#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/lib/libsdsl.a)
#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort.a)
#target_link_libraries(qdags ${CMAKE_SOURCE_DIR}/external/sdsl-lite/build/external/libdivsufsort/lib/libdivsufsort64.a)

add_subdirectory(stdinclude)

message("faux_std_include ${KOKKOS_INCLUDE}")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/stdinclude)
include_directories(${KOKKOS_INCLUDE})

add_executable(main main.cpp)

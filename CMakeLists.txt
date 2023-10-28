cmake_minimum_required(VERSION 3.16)
project(image_binarization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)

add_compile_options(-Wall -Wextra -Wshadow -pedantic -Werror)

include_directories(include)
file(GLOB_RECURSE BINARIZATION_SRC_DIR CONFIGURE_DEPENDS "src/*.cpp")

add_library(binarization_lib ${BINARIZATION_SRC_DIR})
target_link_libraries(binarization_lib PUBLIC OpenMP::OpenMP_CXX)
add_subdirectory(play)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  add_compile_options(-g -Og
    -fsanitize=address -fno-omit-frame-pointer -fconcepts-diagnostics-depth=2)
  add_link_options(-fsanitize=address -fno-omit-frame-pointer)

elseif()
  add_compile_options(-O2)
endif()

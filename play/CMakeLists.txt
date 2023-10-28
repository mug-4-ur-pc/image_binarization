find_package(OpenImageIO REQUIRED)

add_executable(binarize main.cpp)
target_include_directories(binarize PRIVATE ${OpenImageIO_INCLUDE_DIRS})
target_link_libraries(binarize PUBLIC binarization_lib)
target_link_libraries(binarization_lib PRIVATE OpenImageIO)
target_link_libraries(binarization_lib PRIVATE OpenImageIO_Util)

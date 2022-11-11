cmake_minimum_required(VERSION 3.23)
project(list_c C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main_exo1.c)
set(SOURCE_FILES2 main_exo2.c)

add_executable(Dm1_exo1 ${SOURCE_FILES})
add_executable(Dm1_exo2 ${SOURCE_FILES2})

include_directories(lib_exo1 lib_exo2)
add_subdirectory(lib_exo1)
add_subdirectory(lib_exo2)

target_link_libraries(Dm1_exo1 lib_exo1)
target_link_libraries(Dm1_exo2 lib_exo2)


add_subdirectory(Google_tests)
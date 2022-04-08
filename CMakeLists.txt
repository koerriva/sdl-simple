cmake_minimum_required(VERSION 3.0)

project(sdl-simple)

set(CMAKE_CXX_STADNARD 17)
set(PROJECT_SOURCE_DIR src)

aux_source_directory(src SRC_DIR)

include_directories(src)

add_executable(simple ${SRC_DIR})

target_link_libraries(simple sdl2 sdl2_image)

file(COPY data DESTINATION .)
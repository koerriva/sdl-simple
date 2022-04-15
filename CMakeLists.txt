cmake_minimum_required(VERSION 3.2)

project(sdl-simple)

set(CMAKE_CXX_STADNARD 17)
set(PROJECT_SOURCE_DIR src)

aux_source_directory(src SRC_DIR)

include_directories(src)

add_executable(simple ${SRC_DIR})

target_link_libraries(simple mingw32 sdl2main sdl2 sdl2_image)

# target_link_options(simple PRIVATE -mwindows -static-libgcc -static-libstdc++)
# target_link_options(simple PRIVATE -static -lhid -lsetupapi -mwindows -static-libgcc -static-libstdc++)

file(COPY data DESTINATION .)
file(COPY game.xml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY terrain.tmx DESTINATION ${CMAKE_BINARY_DIR})
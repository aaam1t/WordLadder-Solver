cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 20)

project(wordladder)

include(CMakeRC.cmake)
include_directories(include)

cmrc_add_resource_library(wl-resources resources/4words.txt ALIAS wl::rc NAMESPACE wl)


file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
add_executable(ladderWithFakes ${SOURCES})

target_link_libraries(main PRIVATE wl::rc)
target_link_libraries(ladderWithFakes PRIVATE wl::rc)
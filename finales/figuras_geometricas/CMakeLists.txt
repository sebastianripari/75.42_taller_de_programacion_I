cmake_minimum_required(VERSION 3.0)
project(figuras_geometricas)

SET(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=c++11")

file(GLOB CLIENT_SOURCES "main.cpp")

add_executable(client ${CLIENT_SOURCES})

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS} )
include_directories(${GTKMM_INCLUDE_DIRS})
target_link_libraries(client ${GTKMM_LIBRARIES})

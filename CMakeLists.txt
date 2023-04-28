cmake_minimum_required(VERSION 3.20)

project(nxemu)

set(SOURCES src/main.cpp
            src/loader/nro.cpp
            src/kernel/memory/memory.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(nxemu ${SOURCES})
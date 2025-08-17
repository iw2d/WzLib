cmake_minimum_required(VERSION 3.14)
project(WzLib)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(interface)

add_library(WzLib INTERFACE)

target_include_directories(WzLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(WzLib INTERFACE cxx_std_17)
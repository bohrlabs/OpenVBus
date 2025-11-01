
cmake_minimum_required(VERSION 3.20)
project(OpenVBus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(vbus)
add_subdirectory(vbus-gui)

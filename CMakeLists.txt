cmake_minimum_required(VERSION 3.31)
project(biblioteca_digital_aed)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
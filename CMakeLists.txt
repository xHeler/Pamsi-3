cmake_minimum_required(VERSION 3.10)
project(kolko-krzyzyk)

set(EXECUTABLE RUN)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(source)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true include/*.hpp source/*.cpp)
add_executable(${EXECUTABLE} ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})

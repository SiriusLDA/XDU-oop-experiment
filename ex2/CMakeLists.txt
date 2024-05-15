cmake_minimum_required(VERSION 3.10.0)
project(ex2)
set(CMAKE_CXX_COMPILER "g++")

include(CTest)
enable_testing()

include_directories(./include)
aux_source_directory(./src SrcFiles)


set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(${PROJECT_NAME} ${SrcFiles})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

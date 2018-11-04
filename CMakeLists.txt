cmake_minimum_required(VERSION 3.1)

project(GM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG "Debug Version" on)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

add_subdirectory(src)
add_subdirectory(src/AST)
add_subdirectory(src/Common)
add_subdirectory(src/Type)

include_directories(${PROJECT_SOURCE_PATH}/src/AST)
include_directories(${PROJECT_SOURCE_PATH}/src/Common)
include_directories(${PROJECT_SOURCE_PATH}/src/Type)

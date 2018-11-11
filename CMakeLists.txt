cmake_minimum_required(VERSION 3.1)

project(GM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG "Debug Version" on)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

include_directories(${PROJECT_SOURCE_DIR}/include/GM)
include_directories(${PROJECT_SOURCE_DIR}/include/GM/AST)
include_directories(${PROJECT_SOURCE_DIR}/include/GM/Common)
include_directories(${PROJECT_SOURCE_DIR}/include/GM/Core)
include_directories(${PROJECT_SOURCE_DIR}/include/GM/Type)
include_directories(${PROJECT_SOURCE_DIR}/include/GM/Type/Value)

add_subdirectory(src)
add_subdirectory(src/AST)
add_subdirectory(src/Common)
add_subdirectory(src/Core)
add_subdirectory(src/Type)
add_subdirectory(src/Type/Value)

add_subdirectory(test)

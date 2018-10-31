cmake_minimum_required(VERSION 3.1)

project(GM)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(src/Common)
add_subdirectory(src/Type)

include_directories(${PROJECT_SOURCE_PATH}/src/Common)
include_directories(${PROJECT_SOURCE_PATH}/src/Type)

add_executable(GM src/main.cpp)
target_link_libraries(
    GM
    Common
#    Type
)
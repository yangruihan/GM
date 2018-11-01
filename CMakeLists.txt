cmake_minimum_required(VERSION 3.1)

project(GM)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(src/Common)
add_subdirectory(src/AST)

include_directories(${PROJECT_SOURCE_PATH}/src/Common)
include_directories(${PROJECT_SOURCE_PATH}/src/AST)

aux_source_directory(./src SRC_FILES)

add_executable(GM ${SRC_FILES})
target_link_libraries(
    GM
    Common
    AST
)
aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS ./*.hpp)
file(GLOB GM_HEADERS ./*.h)

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Debug")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Release")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

add_executable(
    GM
    ${SRC_FILES}
    ${GM_HEADERS_PLUS}
    ${GM_HEADERS}
)

target_link_libraries(
    GM
    AST
    Common
    Type
    Type_Value
)

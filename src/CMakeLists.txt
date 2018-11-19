aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS "${PROJECT_SOURCE_DIR}/include/GM/*.hpp")
file(GLOB GM_HEADERS "${PROJECT_SOURCE_DIR}/include/GM/*.h")
file(GLOB_RECURSE GM_ESTD_HEADERS "${PROJECT_SOURCE_DIR}/vendor/estd/include/estd/*.h")
file(GLOB_RECURSE GM_ESTD_HEADERS_PLUS "${PROJECT_SOURCE_DIR}/vendor/estd/include/estd/*.hpp")

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})
source_group("Headers/estd" FILES ${GM_ESTD_HEADERS})
source_group("Headers/estd" FILES ${GM_ESTD_HEADERS_PLUS})

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
    ${GM_ESTD_HEADERS}
    ${GM_ESTD_HEADERS_PLUS}
)

target_link_libraries(
    GM
    optimized
    Core
    Common
    AST
    Type
    Type_Value
)

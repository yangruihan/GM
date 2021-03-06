aux_source_directory(. SRC_FILES)
aux_source_directory(./Interpreter T_INTERPRETER_SRC)
aux_source_directory(./Memory T_MEMORY_SRC)
aux_source_directory(./Value T_VALUE_SRC)

file(GLOB_RECURSE GM_HEADERS_PLUS ./*.hpp)
file(GLOB_RECURSE GM_HEADERS ./*.h)
file(GLOB_RECURSE GM_GTEST_HEADERS "${PROJECT_SOURCE_DIR}/include/gtest/*.h")
file(GLOB_RECURSE GM_GMOCK_HEADERS "${PROJECT_SOURCE_DIR}/include/gmock/*.h")
file(GLOB_RECURSE GM_ESTD_HEADERS "${PROJECT_SOURCE_DIR}/vendor/estd/include/estd/*.h")
file(GLOB_RECURSE GM_ESTD_HEADERS_PLUS "${PROJECT_SOURCE_DIR}/vendor/estd/include/estd/*.hpp")

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})
source_group("Headers/gtest" FILES ${GM_GTEST_HEADERS})
source_group("Headers/gmock" FILES ${GM_GMOCK_HEADERS})
source_group("Headers/estd" FILES ${GM_ESTD_HEADERS})
source_group("Headers/estd" FILES ${GM_ESTD_HEADERS_PLUS})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/gmock")
include_directories("${PROJECT_SOURCE_DIR}/include/gtest")
include_directories("${PROJECT_SOURCE_DIR}/test")
include_directories("${PROJECT_SOURCE_DIR}/vendor/estd/include")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Test")

add_executable(
    GM_test
    ${SRC_FILES}
    ${T_INTERPRETER_SRC}
    ${T_MEMORY_SRC}
    ${T_VALUE_SRC}
    ${GM_HEADERS_PLUS}
    ${GM_HEADERS}
    ${GM_GTEST_HEADERS}
    ${GM_GMOCK_HEADERS}
    ${GM_ESTD_HEADERS}
    ${GM_ESTD_HEADERS_PLUS}
)

get_static_lib_path(gtest gmock GMOCKD_LIB GMOCK_LIB)
get_static_lib_path(gtest gtest GTESTD_LIB GTEST_LIB)

message(STATUS "-+ GMOCKD_LIB: ${GMOCKD_LIB}")
message(STATUS "-+ GMOCK_LIB: ${GMOCK_LIB}")
message(STATUS "-+ GTESTD_LIB: ${GTESTD_LIB}")
message(STATUS "-+ GTEST_LIB: ${GTEST_LIB}")

if (WIN32 OR MSVC)
    target_link_libraries(
        GM_test
        Core
        Common
        AST
        Type
        Type_Value
        debug ${GMOCKD_LIB} optimized ${GMOCK_LIB}
        debug ${GTESTD_LIB} optimized ${GTEST_LIB}
    )
else()
    target_link_libraries(
        GM_test
        Core
        Common
        AST
        Type
        Type_Value
        debug ${GMOCKD_LIB} optimized ${GMOCK_LIB}
        debug ${GTESTD_LIB} optimized ${GTEST_LIB}
        pthread
    )
endif()

aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS ./*.hpp)
file(GLOB GM_HEADERS ./*.h)
file(GLOB_RECURSE GM_GTEST_HEADERS "${PROJECT_SOURCE_DIR}/include/gtest/*.h")
file(GLOB_RECURSE GM_GMOCK_HEADERS "${PROJECT_SOURCE_DIR}/include/gmock/*.h")

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})
source_group("Headers" FILES ${GM_GTEST_HEADERS})
source_group("Headers" FILES ${GM_GMOCK_HEADERS})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/gmock")
include_directories("${PROJECT_SOURCE_DIR}/include/gtest")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Test")

add_executable(
    GM_test
    main.cpp
    ${GM_HEADERS_PLUS}
    ${GM_HEADERS}
    ${GM_GTEST_HEADERS}
    ${GM_GMOCK_HEADERS}
)

target_link_libraries(
    GM_test
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgmock_main.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgmock.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgtest_main.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgtest.a
    pthread
)

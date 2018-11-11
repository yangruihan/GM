aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS ./*.hpp)
file(GLOB GM_HEADERS ./*.h)

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/gmock")
include_directories("${PROJECT_SOURCE_DIR}/include/gtest")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Test")

add_executable(
    GM_test
    main.cpp
)

target_link_libraries(
    GM_test
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgmock_main.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgmock.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgtest_main.a
    ${PROJECT_SOURCE_DIR}/libs/gtest/libgtest.a
    pthread
)

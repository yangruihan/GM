aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS "${PROJECT_SOURCE_DIR}/include/GM/Token/*.hpp")
file(GLOB GM_HEADERS "${PROJECT_SOURCE_DIR}/include/GM/Token/*.h")

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})

add_library(
    Token
    ${SRC_FILES}
    ${GM_HEADERS_PLUS}
    ${GM_HEADERS}
)

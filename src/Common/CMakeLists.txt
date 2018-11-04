aux_source_directory(. SRC_FILES)

file(GLOB GM_HEADERS_PLUS ./*.hpp)
file(GLOB GM_HEADERS ./*.h)

source_group("Headers" FILES ${GM_HEADERS_PLUS})
source_group("Headers" FILES ${GM_HEADERS})

add_library(
    Common
    ${SRC_FILES}
    ${GM_HEADERS_PLUS}
    ${GM_HEADERS}
)

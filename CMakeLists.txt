cmake_minimum_required(VERSION 3.1)

project(GM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG "Debug Version" on)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

function(find_library_in_proj LIB_NAME SUB_FOLDER OUT)

    if (WIN32 OR MSVC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
    elseif (UNIX)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so")
    endif()      

    find_library(FOUND_${LIB_NAME}_STATIC
        NAMES 
        ${LIB_NAME}
        HINTS
        "${PROJECT_SOURCE_DIR}/*"
        "${PROJECT_SOURCE_DIR}/libs/*"
        "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/*"
        "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/*/*"
    )

    if (FOUND_${LIB_NAME}_STATIC)
        get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
    else()
        message(SEND_ERROR "Unable to find library ${LIB_NAME}")
    endif()

    set(${OUT} ${ABS_FILE} PARENT_SCOPE)

endfunction()

include_directories("${PROJECT_SOURCE_DIR}/include/GM")
include_directories("${PROJECT_SOURCE_DIR}/include/GM/AST")
include_directories("${PROJECT_SOURCE_DIR}/include/GM/Common")
include_directories("${PROJECT_SOURCE_DIR}/include/GM/Core")
include_directories("${PROJECT_SOURCE_DIR}/include/GM/Type")
include_directories("${PROJECT_SOURCE_DIR}/include/GM/Type/Value")
include_directories("${PROJECT_SOURCE_DIR}/vendor/estd/include")

add_subdirectory(src)
add_subdirectory(src/AST)
add_subdirectory(src/Common)
add_subdirectory(src/Core)
add_subdirectory(src/Type)
add_subdirectory(src/Type/Value)

add_subdirectory(test)

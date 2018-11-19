cmake_minimum_required(VERSION 3.1)

project(GM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG "Debug Version" on)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

function(get_static_lib_path SUB_FOLDER LIB_NAME DEBUG_OUT RELEASE_OUT)
    if (WIN32 OR MSVC)
        set(${DEBUG_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/win32/debug/${LIB_NAME}.lib" PARENT_SCOPE)
        set(${RELEASE_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/win32/release/${LIB_NAME}.lib" PARENT_SCOPE)
        message(STATUS "Get static lib debug: ${DEBUG_OUT}")
        message(STATUS "Get static lib release: ${RELEASE_OUT}")
    elseif (UNIX)
        set(${DEBUG_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/unix/debug/${LIB_NAME}.a" PARENT_SCOPE)
        set(${RELEASE_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/unix/release/${LIB_NAME}.a" PARENT_SCOPE)
        message(STATUS "Get static lib debug: ${DEBUG_OUT}")
        message(STATUS "Get static lib release: ${RELEASE_OUT}")
    endif()
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

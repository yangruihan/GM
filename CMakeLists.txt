cmake_minimum_required(VERSION 3.1)

project(GM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# ---------- OPTIONS ----------
option(DEBUG "Debug Version" off)
option(COMMAND_LINE "Command Line Flag" off)

message(STATUS "* DEBUG FLAG: ${DEBUG}")
message(STATUS "* COMMAND LINE FLAG: ${COMMAND_LINE}")

if(COMMAND_LINE)
    add_definitions(-DCOMMAND_LINE)
endif(COMMAND_LINE)

if(WIN32 OR MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG /MTd")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG /MTd")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
else()
    if(DEBUG)
        add_definitions(-DDEBUG)
    endif(DEBUG)
endif()

# ---------- FUNCTIONS ----------
function(get_static_lib_path SUB_FOLDER LIB_NAME DEBUG_OUT RELEASE_OUT)
    if (WIN32 OR MSVC)
        set(${DEBUG_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/win32/debug/${LIB_NAME}.lib" PARENT_SCOPE)
        set(${RELEASE_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/win32/release/${LIB_NAME}.lib" PARENT_SCOPE)
        message(STATUS "+ Get static lib debug: ${DEBUG_OUT}")
        message(STATUS "+ Get static lib release: ${RELEASE_OUT}")
    elseif (APPLE)
        set(${DEBUG_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/osx/debug/${LIB_NAME}.a" PARENT_SCOPE)
        set(${RELEASE_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/osx/release/${LIB_NAME}.a" PARENT_SCOPE)
        message(STATUS "+ Get static lib debug: ${DEBUG_OUT}")
        message(STATUS "+ Get static lib release: ${RELEASE_OUT}")
    elseif (UNIX)
        set(${DEBUG_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/unix/debug/${LIB_NAME}.a" PARENT_SCOPE)
        set(${RELEASE_OUT} "${PROJECT_SOURCE_DIR}/libs/${SUB_FOLDER}/unix/release/${LIB_NAME}.a" PARENT_SCOPE)
        message(STATUS "+ Get static lib debug: ${DEBUG_OUT}")
        message(STATUS "+ Get static lib release: ${RELEASE_OUT}")
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

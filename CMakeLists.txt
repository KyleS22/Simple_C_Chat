cmake_minimum_required (VERSION 2.6)

project(Simple_C_Chat)

option(test "Build all tests." OFF)
option(DEBUG "Allow debug logs" OFF)

IF (WIN32)
	set(CMAKE_C_FLAGS "-Wall")
ELSE()
	set(CMAKE_C_FLAGS "-g -Wall -Wextra")	
ENDIF()

if(DEBUG)
	add_definitions(-DDEBUG)
endif()

# Version Number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(SOURCE_DIR src)
set(PROJECT_CONFIG_DIR config)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

set(COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/components)
set(LIB_LIST ${COMPONENTS_DIR}/list/include)

configure_file(
	"${PROJECT_CONFIG_DIR}/simpleCChatConfig.h.in"
	"${INCLUDE_DIR}/simpleCChatConfig.h"
)


find_package( Threads )

include_directories(${LIB_LIST})

include_directories("${SOURCE_DIR}")
include_directories("${INCLUDE_DIR}")
include_directories("${LIB_DIR}")

add_subdirectory(${COMPONENTS_DIR})

add_subdirectory(${SOURCE_DIR})



if(test)
	add_subdirectory(${TEST_DIR})

endif()


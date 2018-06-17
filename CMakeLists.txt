cmake_minimum_required (VERSION 2.6)

project(Simple_C_Chat)

option(test "Build all tests. OFF")

# Version Number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(SOURCE_DIR src)
set(PROJECT_CONFIG_DIR config)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)

configure_file(
	"${PROJECT_CONFIG_DIR}/simpleCChatConfig.h.in"
	"${SOURCE_DIR}/simpleCChatConfig.h"
)


find_package( Threads )

include_directories("${SOURCE_DIR}")

add_subdirectory(${SOURCE_DIR})


if(test)
	add_subdirectory(${TEST_DIR})

endif()


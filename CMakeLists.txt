cmake_minimum_required (VERSION 2.6)

project(Simple_C_Chat)

# Version Number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)



set(PROJECT_SOURCE_DIR src)
set(PROJECT_CONFIG_DIR config)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

configure_file(
	"${PROJECT_CONFIG_DIR}/simpleCChatConfig.h.in"
	"${PROJECT_SOURCE_DIR}/simpleCChatConfig.h"
)


include_directories("${PROJECT_SOURCE_DIR}")

add_executable(Simple_C_Chat ${PROJECT_SOURCE_DIR}/helloWorld.c)

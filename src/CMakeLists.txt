
if(WIN32)
	add_library(helloWorldLib helloWindows.c)
else()
	add_library(simpleChatLib linuxChatThreads.c socketHelpers.c simpleChatProtocol.c)
endif()


add_executable(Simple_C_Chat main.c)

target_link_libraries( Simple_C_Chat simpleChatLib list ${CMAKE_THREAD_LIBS_INIT} )

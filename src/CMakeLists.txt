
if(WIN32)
	add_library(helloWorldLib helloWindows.c)
else()
	add_library(helloWorldLib helloWorld.c)
endif()


add_executable(Simple_C_Chat main.c)

target_link_libraries( Simple_C_Chat helloWorldLib ${CMAKE_THREAD_LIBS_INIT} )

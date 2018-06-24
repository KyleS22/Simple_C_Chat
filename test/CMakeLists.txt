
if(test)
	add_executable(runUnitTests testHelloWorld.c)

	target_link_libraries(runUnitTests helloWorldLib)
endif()

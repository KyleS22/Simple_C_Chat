
add_executable(runListTests testList.c)
add_executable(runQueueTests testQueue.c)

target_link_libraries(runListTests list)
target_link_libraries(runQueueTests list)

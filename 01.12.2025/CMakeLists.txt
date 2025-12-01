add_executable(binaryCompare binaryCompare.c)

add_library(queue queue.c)
add_executable(queueTask queueTask.c)
target_link_libraries(queueTask queue)
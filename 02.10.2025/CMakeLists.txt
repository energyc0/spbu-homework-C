add_library(stack stack.c)

add_executable(bracesBalance bracesBalance.c)

target_link_libraries(bracesBalance PRIVATE stack)
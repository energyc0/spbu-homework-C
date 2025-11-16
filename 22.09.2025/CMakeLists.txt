separate_arguments(ASSEMBLY_FLAGS UNIX_COMMAND "${CMAKE_C_FLAGS} -O3")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sorter.S
    COMMAND ${CMAKE_C_COMPILER} ${ASSEMBLY_FLAGS} -S ${CMAKE_CURRENT_SOURCE_DIR}/sorter.c -o ${CMAKE_CURRENT_BINARY_DIR}/sorter.S
    DEPENDS sorter.c sorter.h
    COMMENT "Generate sorter.c assembly file"
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sorter.o
    COMMAND ${CMAKE_C_COMPILER} ${ASSEMBLY_FLAGS} -c ${CMAKE_CURRENT_BINARY_DIR}/sorter.S -o ${CMAKE_CURRENT_BINARY_DIR}/sorter.o
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/sorter.S
    COMMENT "Generate sorter.o object file"
    VERBATIM
)

add_executable(merge_sort "${CMAKE_CURRENT_SOURCE_DIR}/merge_sort.c" ${CMAKE_CURRENT_BINARY_DIR}/sorter.o)

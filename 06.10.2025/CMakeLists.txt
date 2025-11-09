set(SORTED_LIST_LIB_SOURCES sortedList.c)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(SORTED_LIST_LIB_SOURCES ${SORTED_LIST_LIB_SOURCES} sortedListTesting.c)
endif()

add_library(sortedList ${SORTED_LIST_LIB_SOURCES})
add_library(recursiveList recursiveList.c)

add_executable(recursiveList_exercise recursiveList_exercise.c)
add_executable(sortedList_exercise sortedList_exercise.c)

target_link_libraries(recursiveList_exercise PRIVATE recursiveList)
target_link_libraries(sortedList_exercise PRIVATE sortedList)

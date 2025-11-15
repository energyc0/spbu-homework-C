cmake_minimum_required(VERSION 3.25)

project(bracesBalance C)

file(GLOB DIRS LIST_DIRECTORIES true "./??.??.????")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")
message(STATUS "Compiling with flags: ${CMAKE_C_FLAGS}")

foreach(DIR ${DIRS})
    if(EXISTS ${DIR}/CMakeLists.txt)
        message(STATUS "Adding subdirectory: ${DIR}.")
        add_subdirectory(${DIR})
    else()
        message(WARNING "CMakeLists.txt not found in ${DIR}.")
    endif()
endforeach()

cmake_minimum_required(VERSION 3.5)

project(long_arithmetic)



#c compiler flags#
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Os -Ofast")



#default lib linking type#
if(NOT DEFINED LIBRARY_TYPE)
    set(LIBRARY_TYPE SHARED)
endif()



#info#
message(STATUS "OS: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}")
message(STATUS "LIBRARY LINKING TYPE: ${LIBRARY_TYPE}")
message(STATUS "C COMPILER FLAGS: ${CMAKE_C_FLAGS}")



#add sources#
file(GLOB C_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")



#lib#
add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${C_SOURCES})



#include directory#
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")



#test#
add_executable(${PROJECT_NAME}_test "${PROJECT_SOURCE_DIR}/main.c")

target_link_libraries(${PROJECT_NAME}_test PUBLIC ${PROJECT_NAME})
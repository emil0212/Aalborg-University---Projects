cmake_minimum_required(VERSION 3.23)
project(P1_Prototype C)

set(CMAKE_C_STANDARD 99)

add_executable(P1_Prototype main.c menu.c menu.h settings.c settings.h utilities.h utilities.c)

file(COPY User_database/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Store_databases/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
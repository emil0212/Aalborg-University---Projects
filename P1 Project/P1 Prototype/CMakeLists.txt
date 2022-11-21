cmake_minimum_required(VERSION 3.23)
project(P1_Prototype C)

set(CMAKE_C_STANDARD 99)

add_executable(P1_Prototype "Emils Prototype/main.c" "Emils Prototype/menu.c" "Emils Prototype/menu.h" "Emils Prototype/settings.c" "Emils Prototype/settings.h" "Emils Prototype/utilities.h" "Emils Prototype/utilities.c")
add_executable(load_user "Mathiases Prototype/load_user.c")

file(COPY User_database/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lists/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lists2/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
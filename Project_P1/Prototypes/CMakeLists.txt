cmake_minimum_required(VERSION 3.23)
project(P1_Prototype C)

set(CMAKE_C_STANDARD 99)

add_executable(Experimental-prototype "Experimental_prototype/main.c" "Experimental_prototype/menu.c" "Experimental_prototype/menu.h" "Experimental_prototype/database_management.c" "Experimental_prototype/database_management.h" "Experimental_prototype/utilities.c" "Experimental_prototype/utilities.h" "Experimental_prototype/search_management.c" "Experimental_prototype/search_management.h")
add_executable(Project-prototype "Project_prototype/main.c" "Project_prototype/main.h" "Project_prototype/file_management.c" "Project_prototype/file_management.h" "Project_prototype/distance.c" "Project_prototype/distance.h" "Project_prototype/run_time.c" "Project_prototype/run_time.h")

file(COPY "Experimental_prototype/Databases/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Project_prototype/Lists/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Project_prototype/Lists2/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
cmake_minimum_required(VERSION 3.23)
project(P1_Prototype C)

set(CMAKE_C_STANDARD 99)

add_executable(Experimental-prototype "Prototypes/Experimental_prototype/main.c" "Prototypes/Experimental_prototype/menu.c" "Prototypes/Experimental_prototype/menu.h" "Prototypes/Experimental_prototype/settings.c" "Prototypes/Experimental_prototype/settings.h" "Prototypes/Experimental_prototype/utilities.h" "Prototypes/Experimental_prototype/utilities.c" "Prototypes/Experimental_prototype/memory.c" "Prototypes/Experimental_prototype/memory.h")
add_executable(Project-prototype "Prototypes/Project_prototype/main.c" "Prototypes/Project_prototype/main.h" "Prototypes/Project_prototype/file_management.c" "Prototypes/Project_prototype/file_management.h" "Prototypes/Project_prototype/distance.c" "Prototypes/Project_prototype/distance.h" "Prototypes/Project_prototype/run_time.c" "Prototypes/Project_prototype/run_time.h")

file(COPY "Prototypes/Experimental_prototype/Databases/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Prototypes/Project_prototype/Lists/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Prototypes/Project_prototype/Lists2/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Project-solution "Project_solution/main.c" "Project_solution/main.h" "Project_solution/store_management.c" "Project_solution/store_management.h" "Project_solution/utilities.c" "Project_solution/utilities.h" "Project_solution/run_time.c" "Project_solution/run_time.h")
add_executable(Experimental-solution "Experimental_solution/main.c" "Experimental_solution/menu.c" "Experimental_solution/menu.h" "Experimental_solution/profile_management.c" "Experimental_solution/profile_management.h" "Experimental_solution/utilities.c" "Experimental_solution/utilities.h")

file(COPY "Experimental_solution/Databases/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Project_solution/groceries_database/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Project_solution/store_database/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Project_solution/product_database/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
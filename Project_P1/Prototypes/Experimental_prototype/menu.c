#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "menu.h"
#include "utilities.h"

#define MAX 30

void login_page()
{
    char temp_username[MAX];
    char temp_password[MAX];

    printf("Please enter your username> \n");
    scanf("%s", temp_username);

    printf("Please enter your password> \n");
    scanf("%s", temp_password);
}

void registration_page()
{
    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    t_user_profile * database = load_database(file, file_name);

    int id = count_lines_in_file(file, file_name);
    t_user_profile new_profile = create_profile(id);

    upload_profile(file, file_name, new_profile, database);

    printf("Succesfully created a profile!\n\n");
    initial_screen();
}

void main_menu(t_user_profile profile)
{
    int choice;

    time_t current_time;
    time(&current_time);

    printf("----------------------------------------\n");
    printf("Session started at %s\n", ctime(&current_time));
    printf("Prototype | Welcome %s\n", profile.name);
    printf("1) View your profile\n");
    printf("2) View your cart\n");
    printf("3) Create a cart\n");
    printf("4) Search\n");
    printf("5) Logout\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("Session ended at %s\n", ctime(&current_time));
            initial_screen();
            break;
        default:
            main_menu(profile);
    }
}

void initial_screen()
{
    int choice;

    printf("1) Login\n");
    printf("2) Register\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            login_page();
            break;
        case 2:
            registration_page();
            break;
        default:
            initial_screen();
    }
}
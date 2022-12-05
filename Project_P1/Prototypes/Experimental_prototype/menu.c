#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "menu.h"
#include "utilities.h"

#define MAX 30

void main_menu(t_user_profile profile);
void login_page(FILE * file, char * file_name);
void registration_page(FILE * file, char * file_name);

void initial_screen()
{
    int choice;

    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    printf("1) Login\n");
    printf("2) Register\n");
    printf("3) Exit\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            login_page(file, file_name);
            break;
        case 2:
            registration_page(file, file_name);
            break;
        case 3:
            printf("Goodbye!\n");
            exit(EXIT_SUCCESS);
        default:
            printf("\n");
            initial_screen();
    }
}

void main_menu(t_user_profile profile)
{
    int choice;

    time_t login_time, logout_time;

    time(&login_time);

    printf("----------------------------------------\n");
    printf("Session started at %s\n", ctime(&login_time));
    printf("Prototype | Welcome %s\n", profile.name);
    printf("1) View your profile\n");
    printf("2) View your cart\n");
    printf("3) Create a cart\n");
    printf("4) Search\n");
    printf("5) Logout\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            time(&logout_time);
            printf("Session ended at %s\n", ctime(&logout_time));
            initial_screen();
            break;
        default:
            main_menu(profile);
    }
}

void login_page(FILE * file, char * file_name)
{
    char temp_username[MAX];
    char temp_password[MAX];

    t_user_profile * database = load_database(file, file_name);

    printf("Please enter your username> \n");
    scanf("%s", temp_username);

    printf("Please enter your password> \n");
    scanf("%s", temp_password);

    int id = 0;
    if (!validate_credentials_in_database(file, file_name, temp_username, temp_password, database, &id)){
        printf("Login failed, please check your credentials and try again\n");
        initial_screen();
    }

    main_menu(database[id]);
}

void registration_page(FILE * file, char * file_name)
{
    t_user_profile * database = load_database(file, file_name);

    int id = count_lines_in_file(file, file_name);
    t_user_profile new_profile = create_profile(id);

    upload_profile(file, file_name, new_profile, database);

    printf("Succesfully created a profile!\n\n");
    initial_screen();
}
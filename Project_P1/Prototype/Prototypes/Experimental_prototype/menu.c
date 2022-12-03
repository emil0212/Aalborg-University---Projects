#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "menu.h"
#include "settings.h"

#define MAX_NAME 30

bool check_login_operation(char * temp_username, char * temp_password, t_user_profile profile)
{
    if (strcmp(profile.username, temp_username) != 0 || strcmp(profile.password, temp_password) != 0)
        return false;

    return true;
}

void login_page()
{
    char temp_username[MAX_NAME];
    char temp_password[MAX_NAME];

    printf("Please enter your username> \n");
    scanf("%s", temp_username);

    printf("Please enter your password> \n");
    scanf("%s", temp_password);

    /*t_user_profile *profiles_in_database = NULL;
    load_user_profiles(profiles_in_database);

    printf("Username & Password> %s, %s\n", temp_username, temp_password);
    printf("Username & Password> %s, %s\n", profiles_in_database[0].username, profiles_in_database[0].password);
    free(profiles_in_database);*/

    //free(profiles_in_database);

    /*if (check_login_operation(temp_username, temp_password, database_profile) == false){
        printf("Invalid login\n");
        login_page();
    }*/

    //main_menu(database_profile);
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
            break;
        default:
            initial_screen();
    }
}
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "menu.h"
#include "utilities.h"

t_user_profile create_user_profile(FILE * file){

    t_user_profile new_profile;

    fscanf(file, "%s %s %u %lf %d %s %s", &new_profile.name, &new_profile.address, &new_profile.transport,
           &new_profile.max_distance, &new_profile.age, &new_profile.username, &new_profile.password);

    /*printf("\n New profile: %s | %s | %u | %lf | %d | %s | %s", new_profile.name, new_profile.address, new_profile.transport,
           new_profile.max_distance, new_profile.age, new_profile.username, new_profile.password);*/

    return new_profile;
}

bool check_login_operation(FILE * file, char * username, char * password, t_user_profile profile){

    if (file == NULL)
        return false;

    if (!strcmp(profile.username, username) || !strcmp(profile.password, password))
        return false;

    return true;
}

void forgot_password(){

}

void register_page(){

}

void login_page(){

    char username[30]; char password[30];

    FILE * file;
    file = fopen("User_Profile.txt", "r");

    printf("Please enter your username> \n");
    scanf("%s", &(*username));

    printf("Please enter your password> \n");
    scanf("%s", &(*password));

    printf("Username: %s | Password: %s\n", username, password);

    t_user_profile database_profile = create_user_profile(file);

    if (check_login_operation(file, username, password, database_profile) == false){
        printf("Invalid login\n");
        login_page();
    }

    main_menu(database_profile);
}

void main_menu(t_user_profile profile){

    int choice;

    time_t current_time;
    time(&current_time);

    printf("----------------------------------------\n");
    printf("Session started at %s\n", ctime(&current_time));
    printf("P1 Prototype | Welcome %s\n", profile.name);
    printf("1) View your profile\n");
    printf("2) View your cart\n");
    printf("3) Create a cart\n");
    printf("4) Search\n");
    printf("5) Logout\n");
    scanf("%d", &choice);
}

void initial_screen(){

    int choice;

    printf("1) Login\n");
    printf("2) Register\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            login_page();
            break;
        case 2:
            register_page();
            break;
        default:
            initial_screen();
    }
}
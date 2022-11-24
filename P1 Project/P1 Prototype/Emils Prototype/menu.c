#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "menu.h"
#include "memory.h"

#define MAX_ARR 255

const char* string_from_enum_transport(e_transport eTransport)
{
    const char *strings[] = {"Walk", "Bycicle", "Car", "Bus"};
    return strings[eTransport];
}

int file_size(FILE * file, char * file_name){
    int count = 0;
    char i;
    file = fopen(file_name, "r");

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    for ( i = getc(file); i != EOF; i = getc(file))
        if (i == '\n')
            count++;

    fclose(file);

    return count;
}

t_user_profile * load_user_profiles(FILE * file)
{
    char            *file_name      = "Userprofiles.txt";
    //file                            = fopen(file_name, "r");
    int             l_file_size     = file_size(file, file_name);
    t_user_profile *user_profile    = malloc(100000 * sizeof(*user_profile));

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < l_file_size; i++){
        fscanf(file, " %s",  user_profile[i].name);
        fscanf(file, " %s",  user_profile[i].address);
        fscanf(file, " %s",  user_profile[i].username);
        fscanf(file, " %s",  user_profile[i].password);

        fscanf(file, " %lf", &user_profile[i].longitude);
        fscanf(file, " %lf", &user_profile[i].latitude);
        fscanf(file, " %lf", &user_profile[i].max_distance);

        fscanf(file, " %d",  &user_profile[i].age);
        fscanf(file, " %u",  &user_profile[i].transport);
    }

    fclose(file);

    return user_profile;
}

t_user_profile create_user_profile(char* name, char* address, char* username, char* password,
                                   double longitude, double latitude, double max_distance,
                                   int age, e_transport transport){
    t_user_profile new_profile;

    new_profile.name = name;
    new_profile.address = address;
    new_profile.username = username;
    new_profile.password = password;
    new_profile.max_distance = max_distance;
    new_profile.age = age;
    new_profile.transport = transport;

    return new_profile;
}

bool check_login_operation(char * temp_username, char * temp_password, t_user_profile profile)
{
    if (strcmp(profile.username, temp_username) != 0 || strcmp(profile.password, temp_password) != 0)
        return false;

    return true;
}

void login_page()
{
    char temp_username[30];
    char temp_password[30];

    printf("Please enter your username> \n");
    scanf("%s", temp_username);

    printf("Please enter your password> \n");
    scanf("%s", temp_password);

    FILE * file;
    char * filename = "Userprofiles.txt";
    file = fopen(filename, "r");

    t_user_profile *profiles_in_database = load_user_profiles(file);

    printf("Username & Password> %s, %s\n", profiles_in_database[0].username, profiles_in_database[0].password);

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
    printf("P1 Prototype | Welcome %s\n", profile.name);
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
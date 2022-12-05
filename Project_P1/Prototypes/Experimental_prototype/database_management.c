#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"

bool check_profile_existence(FILE * file, char * file_name, t_user_profile profile, t_user_profile database[])
{
    if (strcmp(database[profile.id].username, profile.username) == 0 &&
        strcmp(database[profile.id].password, profile.password) == 0)
        return true;

    return false;
}

t_user_profile create_profile(int id)
{
    t_user_profile new_profile;

    new_profile.id = id;

    printf("Please enter your name>\n ");
    scanf("%s", new_profile.name);

    printf("Please enter your age>\n ");
    scanf("%d", &new_profile.age);

    printf("Please enter your address>\n ");
    scanf("%s", new_profile.address);

    printf("Select a username>\n ");
    scanf("%s", new_profile.username);

    printf("Select a password>\n ");
    scanf("%s", new_profile.password);

    //TODO: long & lat | test geolocation conversion with http requests
    new_profile.longitude = 1.1; new_profile.latitude = 1.1;

    printf("Max distance you're willing to travel>\n ");
    scanf("%lf", &new_profile.max_distance);

    printf("Select a transport option>\n ");
    for (int i = 0; i < 4; i++)
    {
        printf("[%d] %s\n", i, string_from_enum_transport(i));
    }

    scanf("%d", &new_profile.transport);

    return new_profile;
}

t_user_profile load_profile(FILE * file, char * file_name, int id)
{
    file = fopen(file_name, "r");

    validate_file_pointer(file);

    t_user_profile new_profile;

    do{
        fscanf(file, "%d %s %s %s %s %lf %lf %lf %d %u",
               &new_profile.id, new_profile.name, new_profile.address, new_profile.username, new_profile.password,
               &new_profile.longitude, &new_profile.latitude, &new_profile.max_distance, &new_profile.age, &new_profile.transport);
    }while (new_profile.id != id);

    fclose(file);

    return new_profile;
}

void upload_profile(FILE * file, char * file_name, t_user_profile profile, t_user_profile database[])
{
    file = fopen(file_name, "a");

    validate_file_pointer(file);

    if (!(check_profile_existence(file, file_name, profile, database)))
        fprintf(file, "%d %s %s %s %s %lf %lf %f %d %u\n", profile.id, profile.name, profile.address, profile.username, profile.password,
            profile.longitude, profile.latitude, profile.max_distance, profile.age, profile.transport);

    fclose(file);
}

t_user_profile * load_database(FILE * file, char * file_name)
{
    int lines_in_file = count_lines_in_file(file, file_name);

    t_user_profile * database = malloc(lines_in_file * sizeof(*database));

    for (int i = 0; i < lines_in_file; i++)
    {
        database[i] = load_profile(file, file_name, i);
    }

    return database;
}
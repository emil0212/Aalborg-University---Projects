#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define BUFFER_SIZE 255

bool check_if_user_exists(char * username1, char * username2){
    if (strcmp(username1, username2) == 0)
        return true;

    return false;
}

//remember to change settings.h & menu.c call
t_user_profile * load_user_profiles()
{
    t_user_profile * user_profile   = NULL;
    FILE * file                     = NULL;
    char * file_name                = "Userprofiles.txt";

    int lines                       = lines_in_file(file, file_name);

    user_profile                    = malloc(100000 * sizeof(*user_profile));



    file                            = fopen(file_name, "r+");

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    printf("lines in file: %d\n", lines);

    char* tempname = NULL; char* tempaddr = NULL; char* tempusr = NULL; char* temppsw = NULL;
    double longi, lati, max_d;
    int age; e_transport transport;

    for (int i = 0; i < lines; i++){
        fscanf(file, "%s %s %s %s %lf %lf %lf %d %u", tempname, tempaddr, tempusr, temppsw, &longi, &lati,
               &max_d, &age, &transport);

        t_user_profile new_profile = create_user_profile(tempname, tempaddr, tempusr, temppsw, longi, lati, max_d, age, transport);

        user_profile[i] = new_profile;
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
    new_profile.longitude = longitude;
    new_profile.latitude = latitude;
    new_profile.max_distance = max_distance;
    new_profile.age = age;
    new_profile.transport = transport;

    return new_profile;
}

void upload_user_profile(FILE * file, char * file_name, t_user_profile profile){

    //t_user_profile * profiles = load_user_profiles();

    //printf("\nDatabase: %s %s", profiles[0].username, profiles[0].password);

    /*file = fopen(file_name, "r");

    fclose(file);*/

    /* TODO:
     * a) Scan through the file and check if usernames exist before uploading a profile
     * b) Get load_user_profiles(); to work
     * c) Find a way to get append to work so it writes to the end of the file
     * */

    t_user_profile * database_profiles = load_user_profiles();

    printf("First username in database: %s\n", database_profiles[0].username);

    file = fopen(file_name, "a");

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    /*fprintf(file, "%s %s %s %s %lf %lf %f %d %u", profile.name, profile.address, profile.username, profile.password,
            profile.longitude, profile.latitude, profile.max_distance, profile.age, profile.transport);*/

    fclose(file);
}

void initialise_admin_profile()
{
    FILE * file = NULL;

    t_user_profile admin_profile = create_user_profile("Admin", "Syria", "admin", "admin",
                                                       69, 69, 10000, 420, Bus);

    upload_user_profile(file, "Userprofiles.txt", admin_profile);
}
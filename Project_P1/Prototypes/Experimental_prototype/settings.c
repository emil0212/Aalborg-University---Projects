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

t_user_profile * load_user_profiles(FILE * file, char * file_name)
{
    file = fopen(file_name, "r");

    int lines = lines_in_file(file, file_name);

    printf("lines in file: %d\n", lines);

    t_user_profile * user_profiles = malloc(lines * sizeof(*user_profiles));

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char tempname[30]; char tempaddr[30]; char tempusr[30]; char temppsw[30];
    double longi, lati, max_d; int age; e_transport transport;

    for (int i = 0; i < lines; i++){
        fscanf(file, "%s %s %s %s %lf %lf %lf %d %u", tempname, tempaddr, tempusr, temppsw, &longi, &lati,
               &max_d, &age, &transport);

        t_user_profile new_profile = create_user_profile(tempname, tempaddr, tempusr, temppsw,
                                                         longi, lati, max_d, age, transport);

        user_profiles[i] = new_profile;
    }


    fclose(file);

    return user_profiles;
}

t_user_profile create_user_profile(char* name, char* address, char* username, char* password,
                                   double longitude, double latitude, double max_distance, int age,
                                   e_transport transport){
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
    /* TODO:
     * a) Scan through the file and check if usernames exist before uploading a profile
     * b) Get load_user_profiles(); to work
     * c) Find a way to get append to work so it writes to the end of the file
     * */
    file = fopen(file_name, "a");

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }


    fprintf(file, "%s %s %s %s %lf %lf %f %d %u\n", profile.name, profile.address, profile.username, profile.password,
            profile.longitude, profile.latitude, profile.max_distance, profile.age, profile.transport);

    fclose(file);

    t_user_profile * database_profiles = load_user_profiles(file, file_name);

    printf("First username in database: %s\n", database_profiles[0].password);
}

void initialise_admin_profile()
{
    FILE * file = NULL;

    t_user_profile admin_profile = create_user_profile("Admin", "Syria", "admin", "admin",
                                                       69, 69, 10000, 420, Bus);

    upload_user_profile(file, "Userprofiles.txt", admin_profile);
}
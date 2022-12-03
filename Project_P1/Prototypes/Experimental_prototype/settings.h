#ifndef P1_PROTOTYPE_SETTINGS_H
#define P1_PROTOTYPE_SETTINGS_H

#endif //P1_PROTOTYPE_SETTINGS_H

#include <stdbool.h>

typedef enum transport_options{Walk, Bicycle, Car, Bus}e_transport;

typedef struct shopping_list_struct{
    int         id;
    char*       name;
    int         price;
    bool        discount;
}t_shopping_list;

typedef struct user_profile_struct{
    char*       name;
    char*       address;
    char*       username;
    char*       password;
    double      longitude;
    double      latitude;
    double      max_distance;
    int         age;
    e_transport transport;
}t_user_profile;

t_user_profile * load_user_profiles();
t_user_profile create_user_profile(char* name, char* address, char* username, char* password,
                                   double longitude, double latitude, double max_distance,
                                   int age, e_transport transport);
void initialise_admin_profile();


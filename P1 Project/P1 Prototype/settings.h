#ifndef P1_PROTOTYPE_SETTINGS_H
#define P1_PROTOTYPE_SETTINGS_H

#endif //P1_PROTOTYPE_SETTINGS_H

typedef enum transport_options{Walk, Bycicle, Car, Bus}e_transport;

typedef struct user_profile_struct{
    char*       name;
    char*       address;
    e_transport transport;
    double         max_distance;
    int         age;
    char*       username;
    char*       password;
}t_user_profile;

typedef struct cart_profile_struct{

}t_cart_options;
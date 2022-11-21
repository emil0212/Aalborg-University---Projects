#ifndef P1_PROTOTYPE_MENU_H
#define P1_PROTOTYPE_MENU_H

#endif //P1_PROTOTYPE_MENU_H

#include "settings.h"

typedef struct user_profile_struct{
    char*       name;
    char*       address;
    e_transport transport;
    double         max_distance;
    int         age;
    char*       username;
    char*       password;
}t_user_profile;

void main_menu(t_user_profile);
void initial_screen();
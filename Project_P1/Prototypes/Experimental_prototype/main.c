#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "menu.h"

#define USER_AMOUNT 10
#define WORD_SIZE   15

int main() {
    srand(time(NULL));

    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    t_user_profile * database = load_database(file, file_name);

    t_user_profile admin_profile = {0, "Admin", "Denmark", "admin", "admin", 69, 69, 10000, 420, Bus};
    upload_profile(file, file_name, admin_profile, database);

    for (int i = 0; i < count_lines_in_file(file, file_name); i++)
    {
        printf("Username of user id [%d] = %s\n", database[i].id, database[i].username);
    }

    printf("Lines: %d\n", count_lines_in_file(file, file_name));

    initial_screen();
    return 0;
}
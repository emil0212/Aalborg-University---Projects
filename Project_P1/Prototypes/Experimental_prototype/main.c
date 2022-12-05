#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "menu.h"

void debug_admin_profile(FILE * file, char * file_name){
    t_user_profile * database = load_database(file, file_name);
    t_user_profile admin_profile = {count_lines_in_file(file, file_name), "Admin", "Vesterbro_69", "admin", "admin", 69, 69, 10000, 420, Bus};

    upload_profile(file, file_name, admin_profile, database);
}

int main() {
    srand(time(NULL));

    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    debug_admin_profile(file, file_name);

    initial_screen();

    return 0;
}
#include <stdio.h>
#include "utilities.h"
#include "menu.h"

int main() {
    initialise_admin_profile();
    //initial_screen();


    /*
    // this is a test
    char str1[20], str2[20], str3[20];
    int year;
    FILE * fp;

    fp = fopen ("Test.txt", "w+");
    fprintf(fp, "%s\n%s\n%s\n%d\n", "We", "are", "in", 2013);
    fclose(fp);

    printf("lines_in_file: %d\n", lines_in_file(fp, "Test.txt"));

    fp = fopen ("Test.txt", "r");
    fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
    fclose(fp);

    printf("fscanf: %s %s %s %d", str1, str2, str3, year);*/

    return 0;
}


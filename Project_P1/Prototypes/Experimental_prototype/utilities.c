#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"


const char* string_from_enum_transport(e_transport eTransport)
{
    const char *strings[] = {"Walk", "Bicycle", "Car", "Bus"};
    return strings[eTransport];
}

int lines_in_file(FILE * file, char *file_name){
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




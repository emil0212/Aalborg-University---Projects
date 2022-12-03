#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"


const char* string_from_enum_transport(e_transport eTransport)
{
    const char *strings[] = {"Walk", "Bicycle", "Car", "Bus"};
    return strings[eTransport];
}

int lines_in_file(FILE * file, char *file_name){
    int count_lines = 0;
    char chr;

    file = fopen(file_name, "r");

    if (file == NULL){
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    chr = getc(file);
    while (chr != EOF)
    {

        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }

        chr = getc(file);
    }
    fclose(file);

    return count_lines;
}




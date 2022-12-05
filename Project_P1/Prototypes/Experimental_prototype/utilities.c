#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

const char* string_from_enum_transport(e_transport eTransport)
{
    const char *strings[] = {"Walk", "Bicycle", "Car", "Bus"};
    return strings[eTransport];
}

void validate_file_pointer(FILE * file)
{
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
}

int count_lines_in_file(FILE * file, char *file_name){
    int count_lines = 0;

    file = fopen(file_name, "r");
    validate_file_pointer(file);

    char chr = getc(file);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

#define SECONDS_PER_WEEK   (7 * 24 * (60 * 60))
#define SECONDS_PER_DAY    (24 * (60 * 60))
#define SECONDS_PER_HOUR   (60 * 60)
#define SECONDS_PER_MINUTE (60)

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

void session_time_calculator(int input){
    int min, hour;

    input    = input % SECONDS_PER_WEEK;
    input    = input % SECONDS_PER_DAY;

    hour     = input / SECONDS_PER_HOUR;
    input    = input % SECONDS_PER_HOUR;

    min      = input / SECONDS_PER_MINUTE;
    input    = input % SECONDS_PER_MINUTE;

    printf("Session was active for %d hours, %d minutes, %d seconds\n\n", hour, min, input);
}
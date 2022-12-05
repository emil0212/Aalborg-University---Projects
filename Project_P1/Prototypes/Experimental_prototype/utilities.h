#ifndef P1_PROTOTYPE_UTILITIES_H
#define P1_PROTOTYPE_UTILITIES_H

#endif //P1_PROTOTYPE_UTILITIES_H

#include "database_management.h"

const char* string_from_enum_transport(e_transport eTransport);
int count_lines_in_file(FILE * file, char *file_name);
void validate_file_pointer(FILE * file);
void session_time_calculator(int input);
//
// Created by matth on 2024/08/27.
//

#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
#include <stdio.h>
#include <string.h>
#include <cmath>


void generate_file(FILE *file_ptr, int n, signed long int time_value, char file_name[], const char mode[]) {
    if (strcmp(mode, "a") == 0) {
        file_ptr = fopen(file_name, mode);
        fprintf(file_ptr, "%d,%.10f\n", n, time_value * (pow(10, -9)));
        fclose(file_ptr);
    } else if (strcmp(mode, "w") == 0) {
        file_ptr = fopen(file_name, mode);
        fprintf(file_ptr, "input,time\n");
        fclose(file_ptr);
    }
}

#endif //FILE_HANDLING_H

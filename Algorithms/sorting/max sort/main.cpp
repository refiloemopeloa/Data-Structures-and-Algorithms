//
// Created by matth on 2024/09/22.
//

#include "max_sort.h"
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char** argv) {

    char* input=NULL;
    size_t buffer_size = 0;
    printf("Please enter how many elements you would like to enter:\n");
    int input_size = getline(&input, &buffer_size, stdin);
    int num_elements = atoi(input);
    int array[num_elements];

    for (int i=0; i<num_elements;i++) {
        input_size = getline(&input, &buffer_size, stdin);
        array[i] = atoi(input);
    }

    max_sort(array,num_elements);

    return 0;
}
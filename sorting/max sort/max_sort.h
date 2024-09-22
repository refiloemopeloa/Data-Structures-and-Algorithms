//
// Created by matth on 2024/09/22.
//

#ifndef MAX_SORT_H
#define MAX_SORT_H
#include <cstdio>

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int* array, int size) {
    for (int i=0; i<size-1;i++) {
        printf("[%d]:%d\t", i, array[i]);
    }
        printf("[%d]:%d\t\n", size-1, array[size-1]);
}

void max_sort(int* unsorted_array, int num_elements) {
    int max_position = 0;
    printf("Max sorting...\n");
    for (int i=num_elements-1; i>0; i--) {
        max_position = i;
        for (int j=0; j<i;j++) {
            if (unsorted_array[j]>unsorted_array[max_position]) {
                max_position = j;
            }
        }
        swap(&unsorted_array[max_position],&unsorted_array[i]);
        print_array(unsorted_array, num_elements);
    }
}

#endif //MAX_SORT_H

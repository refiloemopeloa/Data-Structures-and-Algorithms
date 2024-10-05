//
// Created by matth on 2024/09/22.
//

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
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

void selection_sort(int* unsorted_array, int num_elements) {
    int min_position = 0;
    printf("Selection sorting...\n");
    for (int i=0; i<=num_elements-2; i++) {
        min_position = i;
        for (int j=i+1; j<=num_elements-1;j++) {
            if (unsorted_array[j]<unsorted_array[min_position]) {
                min_position = j;
            }
        }
        swap(&unsorted_array[min_position],&unsorted_array[i]);
        print_array(unsorted_array, num_elements);
    }
}

#endif //SELECTION_SORT_H

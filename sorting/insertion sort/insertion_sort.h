//
// Created by matth on 2024/09/22.
//

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
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

void insertion_sort(int* unsorted_array, int num_elements) {
    int *current=NULL;
    for (int i=0; i<num_elements;i++) {
        current = &unsorted_array[i];
        for (int j=i-1; j>=0;j--) {
            if (unsorted_array[j]>*current) {
                swap(&unsorted_array[j],current);
                current = &unsorted_array[j];
            }
            print_array(unsorted_array,num_elements);
        }
    }
}

#endif //INSERTION_SORT_H

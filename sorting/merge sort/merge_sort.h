//
// Created by matth on 2024/09/22.
//

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <cstdio>
#include <math.h>

bool beginning = true;

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int* array, int start, int end) {
    for (int i=start; i<end;i++) {
        printf("[%d]:%d\t", i, array[i]);
    }
        printf("[%d]:%d\t\n", end, array[end]);
}

void merge(int *array, int low_left, int high_left, int low_right, int high_right) {
    int temp[high_right+1];
    int i=0, j=0;
    for (i= high_left; i>=low_left; i--) {
        temp[i] = array[i];
    }
    for (j=high_left+1; j<=high_right;j++) {
        temp[high_right+high_left+1-j] = array[j];
    }
    i = low_left;
    j = high_right;
    for (int k=low_left;k<=high_right;k++) {
        if (temp[i] < temp[j]) {
            array[k] = temp[i];
            i++;
        } else {
            array[k] = temp[j];
            j--;
        }
    }
    print_array(temp, low_left, high_right);
}

void merge_sort(int *unsorted_array, int left, int right) {
    if (beginning) {
        printf("Merge sorting...\n");
        beginning=false;
    }
    int mid = 0;
    if ((right - left) > 0) {
        mid = floor((left+right)/2);
        merge_sort(unsorted_array,left, mid);
        merge_sort(unsorted_array,mid+1,right);
        merge(unsorted_array,left, mid, mid+1, right);
    }
}

#endif //INSERTION_SORT_H

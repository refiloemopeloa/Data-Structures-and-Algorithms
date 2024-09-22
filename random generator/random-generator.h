//
// Created by matth on 2024/08/26.
//

#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int rand_num(int n) {
    return rand() % n;
}

#endif //RANDOM_GENERATOR_H

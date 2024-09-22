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

void rand_gen(int n, int *rand_list) {
    srand(time(NULL));
    int exp[2] = {1, -1};
    int sign;
    for (int i = 0; i < n; i++) {
        sign = exp[(rand() % 2)];
        rand_list[i] = sign * i;
    }
    int a, b;
    for (int i = 0; i < n; i++) {
        a = rand_num(n);
        b = rand_num(n);

        swap(&rand_list[a], &rand_list[b]);
    }
}

void print_list(int *rand_list, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d:\t%d\n", i, rand_list[i]);
    }
}


#endif //RANDOM_GENERATOR_H

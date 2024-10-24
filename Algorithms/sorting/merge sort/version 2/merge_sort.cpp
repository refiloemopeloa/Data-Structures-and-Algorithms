#include "random-generator.h"
#include "file_handling.h"
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <omp.h>

void merge(int *array, int low_left, int high_left, int low_right, int high_right) {
    int temp[high_right + 1];
    int i = 0, j = 0;
    for (i = high_left; i >= low_left; i--) {
        temp[i] = array[i];
    }
    for (j = high_left + 1; j <= high_right; j++) {
        temp[high_right + high_left + 1 - j] = array[j];
    }
    i = low_left;
    j = high_right;
    for (int k = low_left; k <= high_right; k++) {
        if (temp[i] < temp[j]) {
            array[k] = temp[i];
            i++;
        } else {
            array[k] = temp[j];
            j--;
        }
    }
}

void merge_sort(int *unsorted_list, int left, int right) {
    int mid_point = 0;
    if ((right - left) > 0) {
        mid_point = floor((left + right) / 2);
        merge_sort(unsorted_list, left, mid_point);
        merge_sort(unsorted_list, mid_point + 1, right);
        merge(unsorted_list, left, mid_point, mid_point + 1, right);
    }
}

int main(int argc, char **argv) {
    int iterations = argc == 2 ? (atoi(argv[1]) + 1) : 10;

    signed long int iterations_list[iterations][2];

    char file_name[] = "merge_sort.csv";
    FILE *file_ptr;

    generate_file(file_ptr, 0, 0, file_name, "w");

    /* Use: For printing unsorted list
    printf("Unsorted list\n");

    print_list(list, size);
    */

    int size = 0;

    omp_set_num_threads(16);

#pragma omp for schedule(static,1)
    for (int iteration = 1; iteration < iterations; iteration++) {
        size = (int) pow(2, iteration);

        int *list = (int *) malloc(size * sizeof(int));

        rand_gen(size, list);

        auto start = std::chrono::high_resolution_clock::now();

        merge_sort(list, 0, size - 1);

        auto stop = std::chrono::high_resolution_clock::now();

        free(list);

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

        iterations_list[iteration - 1][0] = size;
        iterations_list[iteration - 1][1] = duration.count();

        /* Use: For printing sorted list
        printf("Sorted list\n");

        print_list(list, size);
        */
    }


    for (int i = 0; i < iterations - 1; i++)
        generate_file(file_ptr, iterations_list[i][0], iterations_list[i][1], file_name, "a");
    return 0;
}

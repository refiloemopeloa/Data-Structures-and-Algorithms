#include "random-generator.h"
#include "file_handling.h"
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <omp.h>

void bubble_sort(int *unsorted_list, int size) {
    for (int i = size; i > -1; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (unsorted_list[j] > unsorted_list[j + 1]) {
                swap(&unsorted_list[j], &unsorted_list[j + 1]);
            }
        }
    }
}

int main(int argc, char **argv) {
    int iterations = argc == 2 ? (atoi(argv[1]) + 1) : 10;

    signed long int iterations_list[iterations][2];

    char file_name[] = "bubble_sort_no_escape_clause.csv";
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

        bubble_sort(list, size);

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

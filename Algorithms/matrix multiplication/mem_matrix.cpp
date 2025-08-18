#include <iostream>
#include <random>
#include "Matrix.h"

using namespace std;

// #define CLASS

int** initialise(int row_count) {
    int **matrix = (int **) malloc (sizeof(int *) * row_count);
    random_device rd;
    srand(42);
    for (int i = 0; i < row_count; i++) {
        matrix[i] = (int *) malloc (sizeof(int) * row_count);
        for (int j = 0; j < row_count; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }

    return matrix;
}

void print(int **matrix, int row_count) {
    for (int i=0; i < row_count; i++){
        for (int j=0; j < row_count; j++)
        cout << matrix[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void iterative_multiply(int **c, int **a, int **b, int &row_count){
    for (int i=0; i< row_count; i++) {
        for (int j = 0; j< row_count; j++) {
            c[i][j] = 0;
            for (int k = 0; k< row_count; k++) {
                c[i][j] += a[i][k] * b[k][j] ;
            }
        }
    }
}

void clear(int **matrix, int row_count) {
    for (int i = 0; i < row_count; i++)
        free(matrix[i]);
    free(matrix);
}

int main()
{
    int row_count;
    row_count = 3;

    int **C = initialise(row_count);
    cout << "Matrix C" << "\n";
    print(C, row_count);

    #ifdef CLASS
    Matrix M = Matrix(row_count, row_count);

    M.print();
    cout<<endl;
    
    for (int i=0; i< row_count; i++) {
        cout << M[0][i] << " ";
    }

    cout << endl;
    #endif

    clear(C, row_count);

    return 0;
}
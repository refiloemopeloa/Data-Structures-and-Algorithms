#include <iostream>
#include <random>
#include "Matrix.h"

using namespace std;

// #define CLASS

int **initialise(int row_count, char flag = 0)
{
    int **matrix = (int **)malloc(sizeof(int *) * row_count);
    switch (flag)
    {
    case 0:
    {
        random_device rd;
        srand(42);
        for (int i = 0; i < row_count; i++)
        {
            matrix[i] = (int *)malloc(sizeof(int) * row_count);
            for (int j = 0; j < row_count; j++)
            {
                matrix[i][j] = rand() % 10;
            }
        }
        break;
    }

    case 1:
    {
        for (int i = 0; i < row_count; i++)
        {
            matrix[i] = (int *)malloc(sizeof(int) * row_count);
            for (int j = 0; j < row_count; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    break;
    }

    return matrix;
}

void print(int **matrix, int row_count)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void iterative_multiply(int **c, int **a, int **b, int &row_count)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < row_count; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void recursive_multiply(int **A, int **B, int **C, int start_row, int end_row, int start_col, int end_col, int a_row, int a_col, int b_row, int b_col, int row_count, int col_count)
{
    int n = row_count;
    if (n == 1)
    {
        C[0 + start_row][0 + start_col] += A[0 + a_row][0 + a_col] * B[0 + b_row][0 + b_col];
    }
    else
    {
        end_row /= 2;
        end_col /= 2;
        row_count = end_row + 1;
        col_count = end_col + 1;
        recursive_multiply(A, B, C, start_row, end_row, start_col, end_col, a_row, a_col, b_row, b_col, row_count, col_count);
        // start_row += ;
    }
}

void clear(int **matrix, int row_count)
{
    for (int i = 0; i < row_count; i++)
        free(matrix[i]);
    free(matrix);
}

int main()
{
    int row_count;
    row_count = 3;

    int **C = initialise(row_count, 1);
    cout << "Matrix C" << "\n";
    print(C, row_count);

#ifdef CLASS
    Matrix M = Matrix(row_count, row_count);

    M.print();
    cout << endl;

    for (int i = 0; i < row_count; i++)
    {
        cout << M[0][i] << " ";
    }

    cout << endl;
#endif

    clear(C, row_count);

    return 0;
}
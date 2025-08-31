#include <iostream>
#include <random>

using namespace std;

int *initialise(int row_count, char flag = 0)
{
    int *matrix = (int *)malloc(sizeof(int) * row_count * row_count);
    switch (flag)
    {
    case 0:
    {
        random_device rd;
        srand(42);
        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < row_count; j++)
            {
                matrix[i * row_count + j] = rand() % 10;
            }
        }
        break;
    }

    case 1:
    {
        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < row_count; j++)
            {
                matrix[i * row_count + j] = 0;
            }
        }
    }
    break;
    }

    return matrix;
}

void print(int *matrix, int row_count)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
            cout << matrix[i * row_count + j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void iterative_multiply(int *c, int *a, int *b, int &row_count)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
        {
            c[i * row_count + j] = 0;
            for (int k = 0; k < row_count; k++)
            {
                c[i * row_count + j] += a[i * row_count + k] * b[k * row_count + j];
            }
        }
    }
}

void recursive_multiply(int *A, int *B, int *C, int x_c, int y_c, int x_a, int y_a, int x_b, int y_b, int row_count, int col_count, int x_quad, int y_quad)
{
    int n = row_count;

    if (n == 1)
    {
        int a = A[x_a * col_count + y_a];
        int b = B[x_b * col_count + y_b];
        C[x_c * col_count + y_c] += a * b;
    }
    else
    {
        // C[x][y]
        recursive_multiply(A, B, C, x_c / 2 /*+ x_quad*/, y_c / 2 /*+ y_quad*/, x_a / 2, y_a / 2, x_b / 2, y_b / 2, row_count / 2, col_count, x_quad/2, y_quad/2);
        recursive_multiply(A, B, C, x_c / 2 /*+ x_quad*/, y_c / 2 /*+ y_quad*/, x_a / 2, y_a / 2 + 1, x_b / 2 + 1, y_b / 2, row_count / 2, col_count, x_quad/2, y_quad/2);

        // C[x][y+1]
        recursive_multiply(A, B, C, x_c / 2 /*+ x_quad*/, y_c / 2 /*+ y_quad*/ + 1, x_a / 2, y_a / 2, x_b / 2, y_b / 2 + 1, row_count / 2, col_count, x_quad/2, y_quad/2);
        recursive_multiply(A, B, C, x_c / 2 /*+ x_quad*/, y_c / 2 /*+ y_quad*/ + 1, x_a / 2, y_a / 2 + 1, x_b / 2 + 1, y_b / 2 + 1, row_count / 2, col_count, x_quad/2, y_quad/2);

        // C[x+1][y]
        recursive_multiply(A, B, C, x_c / 2 + 1 /*+ x_quad*/, y_c / 2 /*+ y_quad*/, x_a / 2 + 1, y_a / 2, x_b / 2, y_b / 2, row_count / 2, col_count, x_quad/2, y_quad/2);
        recursive_multiply(A, B, C, x_c / 2 + 1 /*+ x_quad*/, y_c / 2 /*+ y_quad*/, x_a / 2 + 1, y_a / 2 + 1, x_b / 2 + 1, y_b / 2, row_count / 2, col_count, x_quad/2, y_quad/2);

        // C[x+1][y+1]
        recursive_multiply(A, B, C, x_c / 2 + 1 /*+ x_quad*/, y_c / 2 + 1 /*+ y_quad*/, x_a / 2 + 1, y_a / 2, x_b / 2, y_b / 2 + 1, row_count / 2, col_count, x_quad/2, y_quad/2);
        recursive_multiply(A, B, C, x_c / 2 + 1 /*+ x_quad*/, y_c / 2 + 1 /*+ y_quad*/, x_a / 2 + 1, y_a / 2 + 1, x_b / 2 + 1, y_b / 2 + 1, row_count / 2, col_count, x_quad/2, y_quad/2);
    }
}

void clear(int *matrix, int row_count)
{
    free(matrix);
}

int main()
{
    int row_count;
    row_count = 4;

    int *C_iter = initialise(row_count, 1);
    cout << "Matrix C" << "\n";
    print(C_iter, row_count);

    int *C_recur = initialise(row_count, 1);
    cout << "Matrix C" << "\n";
    print(C_recur, row_count);

    int *A = initialise(row_count);
    cout << "Matrix A" << "\n";
    print(A, row_count);

    int *B = initialise(row_count);
    cout << "Matrix B" << "\n";
    print(B, row_count);

    iterative_multiply(C_iter, A, B, row_count);

    recursive_multiply(A, B, C_recur, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count, row_count, row_count-1, row_count-1);

    cout << "Matrix C after iterative multiply" << "\n";
    print(C_iter, row_count);

    cout << "Matrix C after recursive multiply" << "\n";
    print(C_recur, row_count);

    clear(C_iter, row_count);
    clear(C_recur, row_count);
    clear(A, row_count);
    clear(B, row_count);

    return 0;
}
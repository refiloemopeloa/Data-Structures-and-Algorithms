#include <iostream>
#include <random>

using namespace std;

int *initialise(int row_count, char flag = 0)
{
    int *matrix = new int[row_count * row_count];
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

int* iterative_multiply( int *a, int *b, int &row_count)
{
    int *c = new int[row_count*row_count];
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
    return c;
}

void clear(int *matrix, int row_count)
{
    delete []matrix;
}

int *add(int* A, int* B, int& row_count) {
    int *C = new int[row_count*row_count];

    for (int i = 0; i < row_count; i++) {
        C[i] = A[i] + B[i];
    }
}

int **partition(int* A, int x_start, int x_end, int y_start, int y_end) {
    int row_count = x_end+1;
    int col_count = y_end + 1;
    int **C = new int*[row_count*col_count];
    
    for (int i = x_start; i <= x_end; i++)
    {
        for (int j = y_start; j < y_end; j++)
        {
            C[(i*col_count)%row_count + j%col_count] = &A[i*col_count + j];
        }
    }
    return C;
}

// int *recursive_multiply(int *A, int *B, int x_c, int y_c, int x_a, int y_a, int x_b, int y_b, int row_count, int col_count) {
//     int n = row_count;
//     int *C = new int[n * n];

//     if (n == 1) {
//         int a = A[x_a * col_count + y_a];
//         int b = B[x_b * col_count + y_b];
//         C[x_c * col_count + y_c] += a * b;
//     } else {
//         int **C_part = partition(C, x_c, row_count-1, y_c, col_count-1);
//         int **A_part = partition(A, x_a, row_count-1, y_a, col_count-1);
//         int **B_part = partition(B, x_b, row_count-1, y_b, col_count-1);
//         *C_part = add(recursive_multiply(*A_part, *B_part, x_c))
//     }
// }

// Function to allocate a 1D array representing a 2D matrix
int* allocateMatrix(int n) {
    int* matrix = new int[n * n];
    for (int i = 0; i < n * n; i++) {
        matrix[i] = 0;
    }
    return matrix;
}

// Copy submatrix from source to destination
void copySubmatrix(int* source, int* dest, int sourceN, int destN, int startRow, int startCol) {
    int dest_old = destN;
    if (destN > sourceN)
        dest_old = sourceN;
    for (int i = 0; i < dest_old; i++) {
        for (int j = 0; j < dest_old; j++) {
            dest[i * destN + j] = source[(startRow + i) * sourceN + (startCol + j)];
        }
    }
}

int *padding(int *C, int& row_count, int& row_count_new) {
    row_count_new = pow(2, (int)log2(row_count)+1);
    int *C_new = allocateMatrix(row_count_new);
    copySubmatrix(C, C_new, row_count, row_count_new, 0, 0);
    return C_new;
}

int *remove_padding(int *C, int& row_count, int& row_count_old) {
    int *C_new = allocateMatrix(row_count_old);
    copySubmatrix(C, C_new, row_count, row_count_old, 0, 0);
    row_count = row_count_old;
    return C_new;

}

int main()
{
    int row_count;
    row_count = 3;
    int row_count_old = row_count;

    int *A = initialise(row_count);

    cout << "Matrix A" << "\n";
    print(A, row_count);
    
    A = padding(A, row_count_old, row_count);
    
    cout << "Matrix A after padding" << "\n";
    print(A, row_count);

    A = remove_padding(A, row_count, row_count_old);

    cout << "Matrix A after removing padding" << "\n";
    print(A, row_count);

    int *B = initialise(row_count);
    cout << "Matrix B" << "\n";
    print(B, row_count);

    int *C_iter = iterative_multiply(A, B, row_count);

    // recursive_multiply(A, B, C_recur, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count - 1, row_count, row_count);

    cout << "Matrix C after iterative multiply" << "\n";
    print(C_iter, row_count);

    // cout << "Matrix C after recursive multiply" << "\n";
    // print(C_recur, row_count);

    clear(C_iter, row_count);
    // clear(C_recur, row_count);
    clear(A, row_count);
    clear(B, row_count);

    return 0;
}
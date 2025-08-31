#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>
#include <algorithm>

// #define PRINT

using namespace std;
using namespace std::chrono;

int *initialise(int row_count)
{
    int *matrix = new int[row_count * row_count];
    random_device rd;
    srand(rd());
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
        {
            matrix[i * row_count + j] = rand();
        }
    }

    return matrix;
}

// Function to allocate a 1D array representing a 2D matrix
int *allocateMatrix(int n)
{
    int *matrix = new int[n * n];
    for (int i = 0; i < n * n; i++)
    {
        matrix[i] = 0;
    }
    return matrix;
}

// Function to deallocate a 1D array
void clear(int *matrix)
{
    delete[] matrix;
}

// Function to print a matrix
void printMatrix(int *matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
}

// Matrix addition: C = A + B
void addMatrices(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = A[i * n + j] + B[i * n + j];
        }
    }
}

// Matrix subtraction: C = A - B
void subtractMatrices(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = A[i * n + j] - B[i * n + j];
        }
    }
}

// Copy submatrix from source to destination
void copySubmatrix(int *source, int *dest, int sourceN, int destN, int startRow, int startCol)
{
    int dest_old = destN;
    if (destN > sourceN)
        dest_old = sourceN;
    for (int i = 0; i < dest_old; i++)
    {
        for (int j = 0; j < dest_old; j++)
        {
            dest[i * destN + j] = source[(startRow + i) * sourceN + (startCol + j)];
        }
    }
}
// Set submatrix in destination from source
void setSubmatrix(int *dest, int *source, int destN, int sourceN, int startRow, int startCol)
{
    for (int i = 0; i < sourceN; i++)
    {
        for (int j = 0; j < sourceN; j++)
        {
            dest[(startRow + i) * destN + (startCol + j)] = source[i * sourceN + j];
        }
    }
}

int *padding(int *C, int &row_count, int &row_count_new)
{
    row_count_new = pow(2, (int)log2(row_count) + 1);
    int *C_new = allocateMatrix(row_count_new);
    copySubmatrix(C, C_new, row_count, row_count_new, 0, 0);
    return C_new;
}

int *remove_padding(int *C, int &row_count, int &row_count_old)
{
    int *C_new = allocateMatrix(row_count_old);
    copySubmatrix(C, C_new, row_count, row_count_old, 0, 0);
    row_count = row_count_old;
    return C_new;
}

// Standard matrix multiplication (for base case and odd-sized matrices)
void standardMultiply(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

auto start_recur = high_resolution_clock::now();
auto stop_recur = high_resolution_clock::now();
double diff_recur;

// Strassen's Matrix Multiplication Algorithm
void strassenMatrixMultiply(int *A, int *B, int *C, int n)
{
    // Base case: n == 1
    if (n == 1)
    {
        C[0] = A[0] * B[0];
        return;
    }

    // Step 1: Divide matrices into n/2 x n/2 submatrices
    int halfSize = n / 2;

    start_recur = high_resolution_clock::now();
    // Allocate submatrices for A and B
    int *A11 = allocateMatrix(halfSize);
    int *A12 = allocateMatrix(halfSize);
    int *A21 = allocateMatrix(halfSize);
    int *A22 = allocateMatrix(halfSize);

    int *B11 = allocateMatrix(halfSize);
    int *B12 = allocateMatrix(halfSize);
    int *B21 = allocateMatrix(halfSize);
    int *B22 = allocateMatrix(halfSize);

    // Extract submatrices from A and B
    copySubmatrix(A, A11, n, halfSize, 0, 0);
    copySubmatrix(A, A12, n, halfSize, 0, halfSize);
    copySubmatrix(A, A21, n, halfSize, halfSize, 0);
    copySubmatrix(A, A22, n, halfSize, halfSize, halfSize);

    copySubmatrix(B, B11, n, halfSize, 0, 0);
    copySubmatrix(B, B12, n, halfSize, 0, halfSize);
    copySubmatrix(B, B21, n, halfSize, halfSize, 0);
    copySubmatrix(B, B22, n, halfSize, halfSize, halfSize);

    // Step 2: Create 10 matrices S1, S2, ..., S10
    int *S1 = allocateMatrix(halfSize);  // S1 = B12 - B22
    int *S2 = allocateMatrix(halfSize);  // S2 = A11 + A12
    int *S3 = allocateMatrix(halfSize);  // S3 = A21 + A22
    int *S4 = allocateMatrix(halfSize);  // S4 = B21 - B11
    int *S5 = allocateMatrix(halfSize);  // S5 = A11 + A22
    int *S6 = allocateMatrix(halfSize);  // S6 = B11 + B22
    int *S7 = allocateMatrix(halfSize);  // S7 = A12 - A22
    int *S8 = allocateMatrix(halfSize);  // S8 = B21 + B22
    int *S9 = allocateMatrix(halfSize);  // S9 = A11 - A21
    int *S10 = allocateMatrix(halfSize); // S10 = B11 + B12
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();

    subtractMatrices(B12, B22, S1, halfSize);
    addMatrices(A11, A12, S2, halfSize);
    addMatrices(A21, A22, S3, halfSize);
    subtractMatrices(B21, B11, S4, halfSize);
    addMatrices(A11, A22, S5, halfSize);
    addMatrices(B11, B22, S6, halfSize);
    subtractMatrices(A12, A22, S7, halfSize);
    addMatrices(B21, B22, S8, halfSize);
    subtractMatrices(A11, A21, S9, halfSize);
    addMatrices(B11, B12, S10, halfSize);

    start_recur = high_resolution_clock::now();
    // Step 3: Recursively compute seven matrix products P1, P2, ..., P7
    int *P1 = allocateMatrix(halfSize); // P1 = A11 * S1
    int *P2 = allocateMatrix(halfSize); // P2 = S2 * B22
    int *P3 = allocateMatrix(halfSize); // P3 = S3 * B11
    int *P4 = allocateMatrix(halfSize); // P4 = A22 * S4
    int *P5 = allocateMatrix(halfSize); // P5 = S5 * S6
    int *P6 = allocateMatrix(halfSize); // P6 = S7 * S8
    int *P7 = allocateMatrix(halfSize); // P7 = S9 * S10
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();

    strassenMatrixMultiply(A11, S1, P1, halfSize);
    strassenMatrixMultiply(S2, B22, P2, halfSize);
    strassenMatrixMultiply(S3, B11, P3, halfSize);
    strassenMatrixMultiply(A22, S4, P4, halfSize);
    strassenMatrixMultiply(S5, S6, P5, halfSize);
    strassenMatrixMultiply(S7, S8, P6, halfSize);
    strassenMatrixMultiply(S9, S10, P7, halfSize);

    start_recur = high_resolution_clock::now();
    // Step 4: Compute the desired submatrices C11, C12, C21, C22
    int *C11 = allocateMatrix(halfSize);
    int *C12 = allocateMatrix(halfSize);
    int *C21 = allocateMatrix(halfSize);
    int *C22 = allocateMatrix(halfSize);

    // Temporary matrices for complex operations
    int *temp1 = allocateMatrix(halfSize);
    int *temp2 = allocateMatrix(halfSize);
    int *temp3 = allocateMatrix(halfSize);
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();

    // C11 = P5 + P4 - P2 + P6
    addMatrices(P5, P4, temp1, halfSize);
    subtractMatrices(temp1, P2, temp2, halfSize);
    addMatrices(temp2, P6, C11, halfSize);

    // C12 = P1 + P2
    addMatrices(P1, P2, C12, halfSize);

    // C21 = P3 + P4
    addMatrices(P3, P4, C21, halfSize);

    // C22 = P5 + P1 - P3 - P7
    addMatrices(P5, P1, temp1, halfSize);
    subtractMatrices(temp1, P3, temp2, halfSize);
    subtractMatrices(temp2, P7, C22, halfSize);

    start_recur = high_resolution_clock::now();
    // Combine submatrices into result matrix C
    setSubmatrix(C, C11, n, halfSize, 0, 0);
    setSubmatrix(C, C12, n, halfSize, 0, halfSize);
    setSubmatrix(C, C21, n, halfSize, halfSize, 0);
    setSubmatrix(C, C22, n, halfSize, halfSize, halfSize);
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();

    // Clean up allocated memory
    start_recur = high_resolution_clock::now();
    clear(A11);
    clear(A12);
    clear(A21);
    clear(A22);
    clear(B11);
    clear(B12);
    clear(B21);
    clear(B22);
    clear(S1);
    clear(S2);
    clear(S3);
    clear(S4);
    clear(S5);
    clear(S6);
    clear(S7);
    clear(S8);
    clear(S9);
    clear(S10);
    clear(P1);
    clear(P2);
    clear(P3);
    clear(P4);
    clear(P5);
    clear(P6);
    clear(P7);
    clear(C11);
    clear(C12);
    clear(C21);
    clear(C22);
    clear(temp1);
    clear(temp2);
    clear(temp3);
    stop_recur = high_resolution_clock::now();
    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();
}

// Square-Matrix-Multiply-Recursive algorithm
void squareMatrixMultiplyRecursive(int *A, int *B, int *C, int n)
{
    // Base case: n == 1
    if (n == 1)
    {
        C[0] = A[0] * B[0];
        return;
    }

    // Partition matrices as in equations (4.9)
    int halfSize = n / 2;

    // Allocate submatrices
    start_recur = high_resolution_clock::now();
    int *A11 = allocateMatrix(halfSize);
    int *A12 = allocateMatrix(halfSize);
    int *A21 = allocateMatrix(halfSize);
    int *A22 = allocateMatrix(halfSize);

    int *B11 = allocateMatrix(halfSize);
    int *B12 = allocateMatrix(halfSize);
    int *B21 = allocateMatrix(halfSize);
    int *B22 = allocateMatrix(halfSize);

    int *C11 = allocateMatrix(halfSize);
    int *C12 = allocateMatrix(halfSize);
    int *C21 = allocateMatrix(halfSize);
    int *C22 = allocateMatrix(halfSize);

    // Temporary matrices for intermediate results
    int *temp1 = allocateMatrix(halfSize);
    int *temp2 = allocateMatrix(halfSize);

    // Extract submatrices from A
    copySubmatrix(A, A11, n, halfSize, 0, 0);
    copySubmatrix(A, A12, n, halfSize, 0, halfSize);
    copySubmatrix(A, A21, n, halfSize, halfSize, 0);
    copySubmatrix(A, A22, n, halfSize, halfSize, halfSize);

    // Extract submatrices from B
    copySubmatrix(B, B11, n, halfSize, 0, 0);
    copySubmatrix(B, B12, n, halfSize, 0, halfSize);
    copySubmatrix(B, B21, n, halfSize, halfSize, 0);
    copySubmatrix(B, B22, n, halfSize, halfSize, halfSize);
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();

    // Compute C11 = A11 * B11 + A12 * B21 (equation 4.11)
    squareMatrixMultiplyRecursive(A11, B11, temp1, halfSize);
    squareMatrixMultiplyRecursive(A12, B21, temp2, halfSize);
    addMatrices(temp1, temp2, C11, halfSize);

    // Compute C12 = A11 * B12 + A12 * B22 (equation 4.12)
    squareMatrixMultiplyRecursive(A11, B12, temp1, halfSize);
    squareMatrixMultiplyRecursive(A12, B22, temp2, halfSize);
    addMatrices(temp1, temp2, C12, halfSize);

    // Compute C21 = A21 * B11 + A22 * B21 (equation 4.13)
    squareMatrixMultiplyRecursive(A21, B11, temp1, halfSize);
    squareMatrixMultiplyRecursive(A22, B21, temp2, halfSize);
    addMatrices(temp1, temp2, C21, halfSize);

    // Compute C22 = A21 * B12 + A22 * B22 (equation 4.14)
    squareMatrixMultiplyRecursive(A21, B12, temp1, halfSize);
    squareMatrixMultiplyRecursive(A22, B22, temp2, halfSize);
    addMatrices(temp1, temp2, C22, halfSize);

    // Combine submatrices into result matrix C
    start_recur = high_resolution_clock::now();
    setSubmatrix(C, C11, n, halfSize, 0, 0);
    setSubmatrix(C, C12, n, halfSize, 0, halfSize);
    setSubmatrix(C, C21, n, halfSize, halfSize, 0);
    setSubmatrix(C, C22, n, halfSize, halfSize, halfSize);

    // Clean up allocated memory
    clear(A11);
    clear(A12);
    clear(A21);
    clear(A22);
    clear(B11);
    clear(B12);
    clear(B21);
    clear(B22);
    clear(C11);
    clear(C12);
    clear(C21);
    clear(C22);
    clear(temp1);
    clear(temp2);
    stop_recur = high_resolution_clock::now();

    diff_recur += duration_cast<nanoseconds>(stop_recur - start_recur).count();
}

bool isEqual(int *A, int *B, int &row_count)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
        {
            if (A[i * row_count + j] != B[i * row_count + j])
                return false;
        }
    }
    return true;
}

int *identity(int &row_count)
{
    int *C = allocateMatrix(row_count);
    for (int i = 0; i < row_count * row_count; i += (row_count + 1))
    {
        C[i] = 1;
    }
    return C;
}

vector<int> prepare_test_samples()
{
    vector<int> samples;
    for (int i = 1; i <= 10; i++)
    {
        samples.push_back(pow(2, i));
    }
    for (int i = 1; i <= 6; i++)
    {
        samples.push_back(pow(3, i));
    }
    for (int i = 1; i <= 4; i++)
    {
        samples.push_back(pow(5, i));
    }

    sort(samples.begin(), samples.end());

    return samples;
}

// Test function
int main(int argc, char **argv)
{
    ofstream outfile("times.csv");
    
    // Write CSV header
    outfile << "input_size,algorithm,time_ns" << endl;
    
    for (int i : prepare_test_samples())
    {
        vector<double> times(3, 0);
        for (int j = 0; j < 3; j++)
        {
            int n = i;
            int n_old;
            bool power = true;

            if (log2(n) - (int)log2(n) != 0)
            {
                power = false;
            }

            // Allocate test matrices
            int *A = initialise(n);
            int *B = initialise(n);

            if (!power)
            {
                n_old = n;
                A = padding(A, n_old, n);
                B = padding(B, n_old, n);
            }

#ifdef PRINT
            cout << "Matrix A:" << endl;
            printMatrix(A, n);
            cout << endl;

            cout << "Matrix B:" << endl;
            printMatrix(B, n);
            cout << endl;
#endif

            // Perform recursive matrix multiplication
            int *C = allocateMatrix(n);

            auto start = high_resolution_clock::now();
            diff_recur = 0;
            squareMatrixMultiplyRecursive(A, B, C, n);
            auto stop = high_resolution_clock::now();

            times[0] += duration_cast<nanoseconds>(stop - start).count() - diff_recur;

            // Test Strassen's algorithm
            int *CStrassen = allocateMatrix(n);
            diff_recur = 0;
            start = high_resolution_clock::now();
            strassenMatrixMultiply(A, B, CStrassen, n);
            stop = high_resolution_clock::now();

            times[1] += duration_cast<nanoseconds>(stop - start).count() - diff_recur;

            // Verify with standard multiplication
            int *CStandard = allocateMatrix(n);
            start = high_resolution_clock::now();
            standardMultiply(A, B, CStandard, n);
            stop = high_resolution_clock::now();

            times[2] += duration_cast<nanoseconds>(stop - start).count();

            if (!power)
            {
                int row_new = n;
                C = remove_padding(C, n, n_old);
                n = row_new;
                CStandard = remove_padding(CStandard, n, n_old);
                n = row_new;
                CStrassen = remove_padding(CStrassen, n, n_old);
            }

#ifdef PRINT
            cout << "Result C = A * B (Recursive):" << endl;
            printMatrix(C, n);
            cout << endl;
            cout << "Result C = A * B (Strassen):" << endl;
            printMatrix(CStrassen, n);
            cout << endl;
            cout << "Verification with standard multiplication:" << endl;
            printMatrix(CStandard, n);
#endif

            if (isEqual(C, CStrassen, n) && isEqual(C, CStandard, n))
            {
                cout << "VERIFIED" << endl;
            }
            else
            {
                cout << "FAILED" << endl;
            }

            // Clean up memory
            clear(A);
            clear(B);
            clear(C);
            clear(CStrassen);
            clear(CStandard);
        }
        
        // Calculate average times
        times[0] /= 3; // Recursive algorithm
        times[1] /= 3; // Strassen algorithm
        times[2] /= 3; // Standard algorithm
        
        // Write times to CSV file
        outfile << i << ",recursive," << times[0]/1e9 << endl;
        outfile << i << ",strassen," << times[1]/1e9 << endl;
        outfile << i << ",standard," << times[2]/1e9 << endl;
        
        // Flush to ensure data is written immediately
        outfile.flush();
    }
    
    outfile.close();
    return 0;
}
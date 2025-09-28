#include <iostream>
#include <vector>

class Matrix {
public:
    std::vector<std::vector<int>> data;
    int rows, cols;
    
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r, std::vector<int>(c, 0));
    }
    
    Matrix(const std::vector<std::vector<int>>& input) {
        data = input;
        rows = input.size();
        cols = input[0].size();
    }
    
    // Copy constructor
    Matrix(const Matrix& other) : data(other.data), rows(other.rows), cols(other.cols) {}
    
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data = other.data;
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    }
    
    int& operator()(int i, int j) {
        return data[i][j];
    }
    
    const int& operator()(int i, int j) const {
        return data[i][j];
    }
    
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Matrix addition
Matrix add(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            C(i, j) = A(i, j) + B(i, j);
        }
    }
    return C;
}

// Matrix subtraction
Matrix subtract(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            C(i, j) = A(i, j) - B(i, j);
        }
    }
    return C;
}

// Extract submatrix
Matrix getSubmatrix(const Matrix& M, int startRow, int startCol, int size) {
    Matrix sub(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sub(i, j) = M(startRow + i, startCol + j);
        }
    }
    return sub;
}

// Set submatrix
void setSubmatrix(Matrix& M, const Matrix& sub, int startRow, int startCol) {
    for (int i = 0; i < sub.rows; i++) {
        for (int j = 0; j < sub.cols; j++) {
            M(startRow + i, startCol + j) = sub(i, j);
        }
    }
}

// Standard matrix multiplication (for base case)
Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.rows;
    Matrix C(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}

// Square-Matrix-Multiply-Recursive algorithm
Matrix squareMatrixMultiplyRecursive(const Matrix& A, const Matrix& B) {
    int n = A.rows;
    Matrix C(n, n);
    
    // Base case
    if (n == 1) {
        C(0, 0) = A(0, 0) * B(0, 0);
        return C;
    }
    
    // For this implementation, we'll handle odd-sized matrices by using standard multiplication
    // In practice, you might want to pad matrices to the next power of 2
    if (n % 2 != 0) {
        return standardMultiply(A, B);
    }
    
    // Partition matrices as in equations (4.9)
    int halfSize = n / 2;
    
    Matrix A11 = getSubmatrix(A, 0, 0, halfSize);
    Matrix A12 = getSubmatrix(A, 0, halfSize, halfSize);
    Matrix A21 = getSubmatrix(A, halfSize, 0, halfSize);
    Matrix A22 = getSubmatrix(A, halfSize, halfSize, halfSize);
    
    Matrix B11 = getSubmatrix(B, 0, 0, halfSize);
    Matrix B12 = getSubmatrix(B, 0, halfSize, halfSize);
    Matrix B21 = getSubmatrix(B, halfSize, 0, halfSize);
    Matrix B22 = getSubmatrix(B, halfSize, halfSize, halfSize);
    
    // Recursive calls as per equations (4.11)-(4.14)
    Matrix C11_part1 = squareMatrixMultiplyRecursive(A11, B11);
    Matrix C11_part2 = squareMatrixMultiplyRecursive(A12, B21);
    Matrix C11 = add(C11_part1, C11_part2);
    
    Matrix C12_part1 = squareMatrixMultiplyRecursive(A11, B12);
    Matrix C12_part2 = squareMatrixMultiplyRecursive(A12, B22);
    Matrix C12 = add(C12_part1, C12_part2);
    
    Matrix C21_part1 = squareMatrixMultiplyRecursive(A21, B11);
    Matrix C21_part2 = squareMatrixMultiplyRecursive(A22, B21);
    Matrix C21 = add(C21_part1, C21_part2);
    
    Matrix C22_part1 = squareMatrixMultiplyRecursive(A21, B12);
    Matrix C22_part2 = squareMatrixMultiplyRecursive(A22, B22);
    Matrix C22 = add(C22_part1, C22_part2);
    
    // Combine results into matrix C
    setSubmatrix(C, C11, 0, 0);
    setSubmatrix(C, C12, 0, halfSize);
    setSubmatrix(C, C21, halfSize, 0);
    setSubmatrix(C, C22, halfSize, halfSize);
    
    return C;
}

// Test function
int main() {
    // Test with a 4x4 matrix
    std::vector<std::vector<int>> dataA = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    std::vector<std::vector<int>> dataB = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };
    
    Matrix A(dataA);
    Matrix B(dataB);
    
    std::cout << "Matrix A:" << std::endl;
    A.print();
    std::cout << std::endl;
    
    std::cout << "Matrix B:" << std::endl;
    B.print();
    std::cout << std::endl;
    
    Matrix C = squareMatrixMultiplyRecursive(A, B);
    
    std::cout << "Result C = A * B:" << std::endl;
    C.print();
    std::cout << std::endl;
    
    // Verify with standard multiplication
    Matrix CStandard = standardMultiply(A, B);
    std::cout << "Verification with standard multiplication:" << std::endl;
    CStandard.print();
    
    return 0;
}
#include "Matrix.h"

Matrix::Matrix() {
    rows = nullptr;
    row_count = 0;
}

Matrix::Matrix(int& row_len, int& col_len)
{
    row_count = col_len;
    rows = new Vector[row_count];
    for (int i=0; i < row_count; i++) {
        rows[i].initialise(row_len);
    }
}

Matrix::~Matrix()
{
    delete[] rows;
}

void Matrix::print() {
    for (int i=0; i<row_count; i++) {
        rows[i].print();
    }
}

Vector Matrix::operator[](int i) {
    return rows[i];
}


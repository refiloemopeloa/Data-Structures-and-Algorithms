#include "Matrix.h"

Matrix::Matrix()
{
    rows = nullptr;
    row_count = 0;
}

Matrix::Matrix(int &row_len, int &col_len)
{
    row_count = col_len;
    rows = new Vector[row_count];
    for (int i = 0; i < row_count; i++)
    {
        rows[i].initialise(row_len);
    }
}

Matrix::~Matrix()
{
    delete[] rows;
}

void Matrix::print()
{
    for (int i = 0; i < row_count; i++)
    {
        rows[i].print();
    }
}

Vector &Matrix::operator[](int i)
{
    return rows[i];
}

void Matrix::iterative_multiply(Matrix &A, Matrix &B)
{
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < row_count; j++)
        {
            rows[i][j] = 0;
            for (int k = 0; k < row_count; k++)
            {
                rows[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int Matrix::get_row_count()
{
    return row_count;
}


void Matrix::recursive_multiply(Matrix &A, Matrix &B, int a_start, int a_end, int b_start, int b_end) {

}
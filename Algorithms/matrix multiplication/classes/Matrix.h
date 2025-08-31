#include "Vector.h"

class Matrix
{
private:
    Vector* rows;
    int row_count;
public:
    Matrix();
    Matrix(int& row_len, int& col_len);
    ~Matrix();
    void print();
    Vector &operator[](int i);
    int get_row_count();
    void iterative_multiply(Matrix &A, Matrix &B);
    void recursive_multiply(Matrix &A, Matrix &B, int a_start, int a_end, int b_start, int b_end);
};


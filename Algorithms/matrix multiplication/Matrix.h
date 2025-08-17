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
    Vector operator[](int i);
};


#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    int row_count;
    row_count = 4;
    Matrix C = Matrix(row_count, row_count);
    
    Matrix B = Matrix(row_count, row_count);
    Matrix A = Matrix(row_count, row_count);

    cout << "Matrix A\n-------------------------------------\n"; 
    A.print();
    cout << "Matrix B\n-------------------------------------\n"; 
    B.print();
    cout << "Matrix C\n-------------------------------------\n"; 
    C.recursive_multiply(A, B, 0, row_count-1, 0, row_count-1);
    C.print();
    cout<<endl;

    return 0;
}
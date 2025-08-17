#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    int row_count;
    row_count = 3;
    Matrix M = Matrix(row_count, row_count);

    M.print();
    cout<<endl;
    
    for (int i=0; i< row_count; i++) {
        cout << M[0][i] << " ";
    }

    cout << endl;

    return 0;
}
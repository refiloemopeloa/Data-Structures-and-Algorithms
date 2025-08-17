#include <iostream>

class Vector
{
private:
    int *cols;
    int items;
public:
    /**
     * @brief Generates a vector of random integers.
     * 
     * @param length The number of elements in the vector.
     * @return A vector of integers.
     */
    Vector();
    ~Vector();
    void initialise(int length);
    void print();
    int &operator[](int i);
};

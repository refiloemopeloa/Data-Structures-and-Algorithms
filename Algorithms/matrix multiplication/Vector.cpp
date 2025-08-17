#include "Vector.h"
#include <cstdlib>
#include <ctime>
#include <random>

Vector::Vector() {
    cols = nullptr;
    items = 0;
}

void Vector::initialise(int length)
{
    std::random_device rd;
    srand(rd());
    items = length;
    cols = new int[items];
    for (int i = 0; i < items; i++)
    {
        cols[i] = rand();
    }
}

void Vector::print() {
    for (int i=0; i<items-1; i++) {
        std::cout << cols[i] << " ";
    }
    std::cout << cols[items-1] << "\n";
}

int &Vector::operator[](int i) {
    return cols[i];
}

Vector::~Vector()
{
}

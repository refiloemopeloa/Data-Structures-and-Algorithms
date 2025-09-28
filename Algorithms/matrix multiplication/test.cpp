#include <iostream>
#include <cstdlib>

using namespace std;

// #define TESTING

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void random(int *list, int len)
{
    for (int i = 0; i < len; i++)
    {
        swap(list[i], list[rand() % len]);
    }
}

void print(int *array, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        cout << array[i] << " ";
    }
    cout << array[len - 1] << endl;
    ;
}

#ifdef TESTING

int main()
{

    srand(time(0));

    int array[] = {1, 2, 3, 4, 5};
    int len = 5;

    print(array, len);

    random(array, len);

    print(array, len);

    return 0;
}
#endif
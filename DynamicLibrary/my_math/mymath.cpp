#include <iostream>
#include "mymath.h"

// g++ -std=c++14 -fPIC -c -o mymath.o mymath.cpp
// gcc -shared -o libmymath.so mymath.o

int my_add(int a, int b)
{
    int result = 0;
    result = a+b;
    std::cout << "Result=" << result << std::endl;
    return result;
}
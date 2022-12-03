#include <iostream>
#include <vector>

using namespace std;

// const int* ptr - Ne mozes menjati vrednost
    // ekvivalent: int const *ptr

// int* const ptr - Ne mozes menjati adresu

void funkcija (const int* ptr)
{

    // *ptr = 5; // Menjas vrednost 

    int x {10};
    ptr = &x; // Menjas adresu

    cout << *ptr << endl;
}


int main ()
{
    int x = 3;
    funkcija(&x);

    return 0;
}
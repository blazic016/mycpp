#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

void printTimes(int x, char c)
{
    for (int i=0;i<x;i++)
    {
        cout << c;
    }
}


int pyramid_not_recrusive(int p)
{
    if (p == 0)
        return 0;


    for (int i=0;i<p;i++)
    {   
        printTimes(abs(i-p), ' ');
        printTimes(i, 'H');
        printTimes(i, 'H');
        cout << endl;
    }

    return 0;
}



void pyramid_recrusive(int p)
{
    if (p == 0)
        return;
    else 
    {
        printTimes(p, ' ');
        printTimes(abs(p-10), 'X');
        printTimes(abs(p-10), 'X');
        cout << endl;

        pyramid_recrusive(p-1);
    }
    return;
}


int main ()
{

    pyramid_recrusive(10);
    return 0;
}
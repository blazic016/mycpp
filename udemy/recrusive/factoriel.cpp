#include <iostream>

using namespace std;


int factoriel(int x)
{
    if (x == 0 || x == 1)
    {
        return 1;
    }

    cout << x << "*" << "factoriel(" << x-1 << ")" << endl;

    return x * factoriel(x-1);
}


int main ()
{

    int x = factoriel(3);
    cout << "Result x: " << x << endl;
    cout << endl;
  
    int y = factoriel(4);
    cout << "Result y: " << y << endl;
    cout << endl;

    // cout << "Result: 3! = " << factoriel(3) << endl;ls
    // cout << endl;
    // cout << "Result: 4! = " << factoriel(4) << endl;

    return 0;
}
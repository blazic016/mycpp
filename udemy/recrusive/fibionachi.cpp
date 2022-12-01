#include <iostream>

using namespace std;


int fibionachi(int x)
{
    if (x == 0)
    {
        return 0;
    }
    else if (x == 1)
    {
        return 1;
    }

    return fibionachi(x-1) + fibionachi(x-2);
}

int main ()
{

    int x = fibionachi(3);
    cout << "Result x: " << x << endl;
    cout << endl;
  
    int y = fibionachi(14);
    cout << "Result y: " << y << endl;
    cout << endl;

    // cout << "Result: 3 = " << fibionachi(3) << endl;
    // cout << endl;
    // cout << "Result: 4 = " << fibionachi(4) << endl;

    return 0;
}
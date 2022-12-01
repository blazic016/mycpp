#include <iostream>
#include <iomanip>

using namespace std;

double penny_doubled_every_day (double penny, int days)
{
    if (days <= 1)
    {
        return penny;
    }
    
    return penny_doubled_every_day(penny*2, days-1);
}

int main ()
{
    double total_save = penny_doubled_every_day(0.1, 5);

    cout << total_save << endl;


    return 0;
}
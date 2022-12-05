#include <iostream>
#include <vector>

using namespace std;


int main ()
{
    vector<int> vec {0};
    
    vec.push_back(6);
    vec.push_back(44);
    vec.push_back(88);
    vec.push_back(22);

    cout << "Size: " << size(vec) << endl;


    for (size_t i = 0; i<size(vec); i++) {
        vec.at(i) = i+10;
    }

    cout << "[ ";
    for (size_t i = 0; i<size(vec); i++) {
        cout << vec.at(i) << " ";
    }
    cout << " ]" << endl;


    for (size_t i = 0; i<size(vec); i++) {
        if (vec.at(i) == 13)
            cout << "Exist number 13" << endl;
    }
    


    return 0;
}
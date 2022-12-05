#include <iostream>
#include <vector>

using namespace std;


typedef struct {             
  int myNum;         
  string myString;   
} myStructure;      

int main ()
{    
    myStructure struktura;
    vector<myStructure> vec;

    cout << "Size " << size(vec) << endl;

    vec.push_back({1, "prvi"});
    cout << "Size " << size(vec) << endl;

    cout << vec.at(0).myNum << endl; 
    cout << vec.at(0).myString << endl; 


    vec.push_back({2, "drugi"});
    cout << "Size " << size(vec) << endl;

    cout << vec.at(1).myNum << endl; 
    cout << vec.at(1).myString << endl; 



    return 0;
}
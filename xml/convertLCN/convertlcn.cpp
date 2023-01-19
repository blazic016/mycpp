#include<iostream>
#include<string>


class convertlcn
{
private: 
    std::string hex_num;
    int num;
public:
    convertlcn(std::string str_hex);

};

convertlcn::convertlcn(std::string str_hex)
    : hex_num(str_hex) 
{
    std::cout << "hex_num=" << hex_num <<  std::endl;
}


int main() {
    
    convertlcn x {"33"};


    return 0;
}

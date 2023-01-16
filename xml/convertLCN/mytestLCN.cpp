#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

int ConvertToLcn(std::string str_hex)
{
    int num_h = 0;
    std::istringstream(str_hex) >> std::hex >> num_h;
    // std::cout << "[ConvertToLcn] hex: " << num_h << std::endl;
    std::bitset<10> num_b(num_h);
    // std::cout << "[ConvertToLcn] bin: " << num_b << '\n';
    int lcn = num_b.to_ullong();
    // std::cout << "[ConvertToLcn] lcn: " << lcn << '\n';
    return lcn;
}

int main()
{
    // Convert from hex string to LCN
    std::string str_hex = "FC04";
    int lcn = ConvertToLcn(str_hex);
    std::cout << "LCN: " << lcn << std::endl;
    return 0;
}
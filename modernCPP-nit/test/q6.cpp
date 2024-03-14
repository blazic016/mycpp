#include <iostream>
#include <tuple>



int main () {
    std::tuple<float, double, int> mytuple(1,2,3);

    float a = 0;
    double b = 0;
    int c = 0;

    // izbuci a i b
    std::tie(a,b,std::ignore) = mytuple;
    std::cout << "a="<< a << std::endl;
    std::cout << "b=" << b << std::endl;
    std::cout << "c=" << c << std::endl;

    std::make_tuple 

    // float a;
    // double b;
    // int c;
    // std::tie<a, b, c> = x
    // std::cout << a;

    return 0;
}
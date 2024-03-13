#include<iostream>

// OLD SCHOOL
// template<typename T>
// T sum(T x) {
//     return x;
// }
// template<typename T, typename... Args>
// T sum(T x, Args... args) {
// return x + sum(args...);
// }

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

int main() {
    auto res = sum(2,2.7,3);
    std::cout << "Rezultat: " << res << std::endl;
    return 0;
}
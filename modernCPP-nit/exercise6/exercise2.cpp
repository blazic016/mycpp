#include<iostream>


template<typename T>
auto min(T value) {
    return value;
}

template<typename T, typename... Args>
auto min(T first, Args... args) {
    T rest = min(args...);
    if (first < rest)
        return first;
    else 
        return rest;
}

int main() {
    auto res = min(2,2.7,3,1);
    std::cout << "Rezultat: " << res << std::endl;
    return 0;
}
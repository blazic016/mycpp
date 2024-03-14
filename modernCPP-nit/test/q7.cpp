
// Write a function template with the variable number of params, 
// where the result of the function is the sum of the odd params.
// For example:
// ```
// foo(1,3,8,7); - result should be 11 (1+3+7)
// foo(5,2,10); //5
// foo(4,6,12); //0
// ```

#include<iostream>

template<typename T>
T foo(T val) {
    return (val % 2 != 0) ? val : 0;
}

template<typename T, typename... Args>
T foo(T first, Args... args) {
    return foo(first) + foo(args...);
}

int main() {
    std::cout << foo(1,3,8,7) << std::endl;
    std::cout << foo(5,2,10,7) << std::endl;
    std::cout << foo(4,6,12) << std::endl;
    return 0;
}
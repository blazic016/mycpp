
// Modify this code (copy it into the answer box and modify it according to the task) so that in the case where **T** is a pointer type, it prints out what the function parameter points to.
// ```
// template<typename T>  
// void foo(T x) {  
//     std::cout << x;  
// }
// ```
// For example, in the case of the code below, the printout should be: 55
// ```
// int i = 5;  
// foo(i);  
// foo(&i);
// #include <iostream>

template<typename T>
void foo(T x) {
    std::cout << x;
}

template<typename T>
void foo(T* x) {
    std::cout << *x;
}

int main () {
    int i = 5;
    foo(i);
    foo(&i);

    return 0;
}
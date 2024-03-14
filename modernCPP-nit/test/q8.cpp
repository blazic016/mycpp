
/*

Expant this code (copy it into the answer box and modify it according to the task)
```
template<typename T>
class Bar {
public:
	Bar(T x) {}
	
	T data;
};
```
so that in the folowing code the variables a and b are the same type `Bar<int>` and, consequently the oputput is 65
```
int i = 5;
Bar a{6};
Bar b{&i};
std::cout << a.data << b.data << std::endl;
```
*/

#include <iostream>

template<typename T>
class Bar {
public:
	Bar(T x) : data{x} {}
    Bar(T* x) : data{*x} {}
	T data;
};

int main () {
    int i = 5;
    Bar a{6};
    Bar b{&i};
    std::cout << a.data << b.data << std::endl;

    return 0;
}
/*

Given the following code with static polimorfphism:
```
template<class T>
struct Base {
	void func () {
		std::cout << "B";
		static_cast<T*>(this)->specific();
	}
};
struct D1 : Base<D1> {
	void specific() {std::cout << "D1";};
};
struct D2 : Base<D2> {
	void specific() {std::cout << "D2";};
};
```
Which of these codes will compile correctly and what will they print if they are correct?

*/


#include <iostream>
#include <vector>

template<class T>
struct Base {
	void func () {
		std::cout << "B";
		static_cast<T*>(this)->specific();
	}
};
struct D1 : Base<D1> {
	void specific() {std::cout << "D1";};
};
struct D2 : Base<D2> {
	void specific() {std::cout << "D2";};
};


int main() {

    // D1 d1;
    // D2 d2;
    // d1.func();      // BD1
    // d2.func();      // BD1BD2
    // d1.specific();  // BD1BD2D1
    // d2.specific();  // BD1BD2D1D2


	D1 x;
	D2 y;
	std::vector<Base&> v = {x, y};
	for (auto it : v) it.func();

    std::cout << std::endl;
    return 0;
}
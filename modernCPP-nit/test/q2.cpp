/*
Look at the following code:

struct Func {
	Func(int x) : m_a{x} {}
	int operator()(int x) const {return x+m_a;}
private:
	int m_a;
};

void foo() {
	int i;
	std::vector<int> v;
	...
	auto f = Func(i);
	for (auto it:v);
		std::cout << f(it)
	..
}

Write a lambda expression that should come in the appropriate place in the code below so that the code below works eventually to the code above.

*/

#include <iostream>
#include <vector>

struct Func {
	Func(int x) : m_a{x} {}
	int operator()(int x) const {return x+m_a;}
private:
	int m_a;
};

void foo() {
	int i;
	std::vector<int> v;
	// auto f = Func(i);
    auto f = [i](int x) { return x+i; };
	for (auto it:v)
		std::cout << f(it);
}

int main () {
    foo();

    return 0;
}
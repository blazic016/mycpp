#include <iostream>

#include <memory>
#include "MyUniquePtr.h"

using namespace std;

// #define myUP std::unique_ptr
#define myUP MyUniquePtr

struct MyClass
{
	MyClass(int a, int b, int c) : x(a), y(b), z(c) {}
	int x, y, z;
};

void foo(const MyClass &x)
{
	cout << x.x;
}

void bar(const MyClass *x)
{
	cout << x->y;
}

myUP<MyClass> makeObjectUP()
{
	// return std::make_unique<MyClass>(); // but we can not implement make_unique at the moment
	return myUP<MyClass>(new MyClass(1, 2, 3));
}

int main()
{
	myUP<MyClass> p;
	p = makeObjectUP();
	foo(*p);
	bar(p.get());
	cout << p->z; // NOTE: do this last; look up -> operator on the Internet

	// Errors: disallow this
	// myUP<MyClass> q{p};
	// myUP<MyClass> r;
	// r = p;

	// @TODO: print "Hi!" from destructor
	return 0;
}

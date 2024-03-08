Task 1
Take MyBigInt from the previous day and rework it so that it dynamically allocates memory for digits. So, instead of using std::array, you should have a pointer to int_least8_t and then allocate an array of 70 elements using new in constructor, delete it in destructor, etc. You do not need to support varying number of digits, i.e. you should still work with maximum 70 digits and therefore all the other code should be changed minimally. Then move-enable the type (add move constructor and move assignment).

Task 2
Implement type MyUniquePtr which will have the same functionalities as standard library type unique_ptr. In exercise4.cpp Download exercise4.cppfile there is code that uses unique_ptr, and your type should be able to replace unique_ptr in that code (i.e. only implement functionalities used by that code).

In file MyUniquePtr.h Download MyUniquePtr.hdefine class template MyUniquePtr. With #define directive on the beginning of main.cpp replace unique_ptr with MyUniquePtr. After that the code should compile and behave the same, whereas commented block of code (“Errors”) should generate compile-time errors. Pay attention to @TODO comment at the end of function main.

Note: Operator -> is a special form of operator. It is always declared as a member function and it doesn’t accept any arguments. It should return pointer to type of field whose name corresponds to the right hand side. Look it up on the Internet if you need more info.

exercise4.cpp
```
#include <iostream>

#include<memory>
#include "MyUniquePtr.h"

using std::cout;


#define myUP std::unique_ptr
//#define myUP MyUniquePtr


struct MyClass {
	MyClass(int a, int b, int c) : x(a), y(b), z(c) {}
	int x, y, z;
};


void foo(const MyClass& x) {
	cout << x.x;
}

void bar(const MyClass* x) {
	cout << x->y;
}

myUP<MyClass> makeObjectUP()
{
	//return std::make_unique<MyClass>(); // but we can not implement make_unique at the moment
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
	//myUP<MyClass> q{p};
	//myUP<MyClass> r;
	//r = p;

	// @TODO: print "Hi!" from destructor
	return 0;
}
```

MyUniquePtr.h
```
#ifndef _MY_UNIQUE_PTR_
#define _MY_UNIQUE_PTR_


#endif
```
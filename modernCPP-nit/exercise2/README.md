Implement type MyBigInt, which can represent very large non-negative integer numbers (up to 70 digits). Implementation of the type is already started in file MyBigInt.hpp Download MyBigInt.hpp. Type should represent numbers as arrays of digits. Implement only functions (methods/operators) that are required for compilation of code in file exercise1.cpp, and its correct execution (in short, those are: print to stream with <<, operator +, constructors, destructor, assignment and literal). In file exercise1.cpp Download exercise1.cppyou also need to implement function for calculating n-th Fibonacci number, but this time rely on MyBigInt.

MyBigInt.hpp
```
#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_
#include <cstdint>
#include <array>

struct MyBigInt {
private:
    static constexpr int size{70};
    std::array<int_least8_t, size> digits;
};

#endif

```


exercise1.cpp
```
﻿#include "MyBigInt.hpp"

#include <iostream>

// Here write the following function:
// MyBigInt fibo(int n);


int main()
{
	MyBigInt k{ 7 };
	k = fibo(9);
	k = k + 5;
	std::cout << k << std::endl;
	k = 7 + fibo(11);
	std::cout << k << std::endl;
	k = 13_mbi;
	std::cout << k << std::endl;
	MyBigInt l = fibo(300);
	if (l != 222232244629420445529739893461909967206666939096499764990979600_mbi) {
		std::cout << "Error!" << std::endl;
		return 1;
	}
	std::cout << l << std::endl;
	return 0;
}
```
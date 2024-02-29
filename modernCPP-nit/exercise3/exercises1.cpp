#include "MyBigInt.hpp"

#include <iostream>

// Here write the following function:
// MyBigInt fibo(int n);

MyBigInt fibo(int n)
{
	if (n == 0)
		return MyBigInt{0};
	if (n == 1)
		return MyBigInt{1};

	MyBigInt f{0};
	MyBigInt s{1};

	for (int i = 2; i <= n; i++)
	{
		MyBigInt temp{s}; // copy ctor
		s = f + s; // copy ctor
		f = temp;
	}
	return s;
}

int main()
{
	MyBigInt k{7}; 			//ctor int
	k = fibo(9); // 34		
	k = k + 5; // 39
	std::cout << k << std::endl;
	k =  7 + MyBigInt(7); // 96
	std::cout << k << std::endl;
	k = 13_mbi;
	std::cout << k << std::endl;
	MyBigInt l = fibo(300);
	if (l != 222232244629420445529739893461909967206666939096499764990979600_mbi)
	{
		std::cout << "Error!" << std::endl;
		return 1;
	}
	std::cout << l << std::endl;
	return 0;
}
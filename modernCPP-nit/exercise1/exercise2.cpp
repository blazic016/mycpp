// g++ -Wall exercise2.cpp -o output && ./output
#include <iostream>
#include <cassert>
#include <cstdint>


// Here implement the following function:
constexpr uint32_t fibo(int n) {
    if (n <= 1)
        return n;
    else
        return fibo(n - 1) + fibo(n - 2);
}

int main()
{
	static_assert(fibo(7) == 13);
	constexpr uint32_t k = fibo(9);
	std::cout << k << std::endl;
	constexpr uint32_t l = fibo(44);
	std::cout << l << std::endl;
	return 0;
}

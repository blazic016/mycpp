Task 1
In the code in file exercise1.cpp Download exercise1.cppwrite four “one liners” (one statement), each at the place of the appropriate comment in the code.

Use STL algorithms and lambda expressions. At each of the four places, the whole solution can be written in one statement/line (you can break it into multiple lines for readability).

Useful thing will be std::back_inserter_iterator and std::back_inserter.

Look and find algorithms that can be of use:

https://en.cppreference.com/w/cpp/algorithmLinks to an external site.

```
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cout;
using std::vector;


template<typename T>
void printElements(const T& c) {
	for (const auto& x : c) {
		cout << x << " ";
	}
	cout << std::endl;
}


int main()
{
	vector<int> first;

	// 1. Set vector elements to 0 .. 99.


	cout << "First:\n";
	printElements(first);

	vector<int> second{first};  // Copy vector first to vector second

	// 2. Modify values of vector "first" by squaring them.


	cout << "\n\nSquares:\n";
	printElements(first);

	int res{
		
		// 3. Calculate the sum of sqared elemenents of "second".

	};
	cout << "\n\nSum of squares: " << res << "\n";
	if (res != 328350)
		return 1; // wrong result

	cout << "\nEven numbers:\n";
	// 4. Print out only even numbers in vector "second".
	
	return 0;
}
```

Task 2
In the resulting code from the previous exercise, replace all lambda expression with explicit function objects. Before that, copy the solution to exercise2.cpp.
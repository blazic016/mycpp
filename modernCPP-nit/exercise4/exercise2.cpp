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

class CreateAndSetElements {
public:
    int operator()() {
		static int value = 0; 
		return value++; 
    }
};

class SquareAllElements {
public:
    void operator()(int &value) {
		value *= value;
    }
};

class SquaredOfAllElements {
public:
    int operator()(int sum, int value) {
		return sum + value*value; 
    }
};

class PrintEvenElements {
public:
    void operator()(int &value) {
		if (value % 2 == 0) 
			cout << value << " ";
    }
};

int main()
{
	std::vector<int> first;
	
	// 1. Set vector elements to 0 .. 99.
	std::generate_n(std::back_inserter(first), 100, CreateAndSetElements());
	cout << "First:\n";
	printElements(first);

	// Copy vector first to vector second
	vector<int> second{first};  

	// 2. Modify values of vector "first" by vv them.
	std::for_each(first.begin(), first.end(), SquareAllElements());
	cout << "\nSquares:\n";
	printElements(first);

	// 3. Calculate the sum of sqared elemenents of "second".
	int res = std::accumulate(second.begin(), second.end(), 0, SquaredOfAllElements());
	cout << "\nSum of squares: " << res << "\n";
	if (res != 328350) {
		std::cout << "wrong result\n";
		return 1;
	}

	// 4. Print out only even numbers in vector "second".
	std::cout << "\nEven numbers:\n";
	std::for_each(first.begin(), first.end(), PrintEvenElements());

	return 0;
}

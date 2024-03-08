Task 1
In file exercise1.cpp Download exercise1.cppdefinition of very simple single linked list is given. In main function there is code that iterates through list in many different ways, but the part that uses range for does not compile. Add code which is need for main function to compile, and the program to execute correctly.  (Do not change the main function)
```
#include <iostream>

struct Node {
	Node() {}
	Node(int e, Node* n) : elem(e), next(n) {}
	int elem = 0;
	Node* next = nullptr;
};

void add(Node& n, int x) {
	n.next = new Node(x, n.next);
}


int main() {
	Node head;
	add(head, 1);
	add(head, 2);
	add(head, 3);
	add(head, 4);
	add(head, 5);

	for (Node* p = head.next; p != nullptr; p = p->next) {
		std::cout << p->elem << " ";
	}
	std::cout << std::endl;

	for (int x : head) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	for (int& x : head) {
		x = 7;
	}
	for (const int& x : head) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
```
Task 2
In file exercise2.cpp Download exercise2.cppimplement function that calculates n-th Fibonacci number. Implement the function so that the rest of the code compiles and executes correctly. Also, make sure that any usage of too big argument in the last line of main function is reported as error in compile-time.
```
﻿#include <iostream>

// Here implement the following function:
// int fibo(int n)


int main()
{
	static_assert(fibo(7) == 34);
	constexpr int k = fibo(9);
	std::cout << k << std::endl;
	constexpr int l = fibo(300); // 300. Fibonacci number is too big for int
}
```


//g++ exercise1.cpp -o output && ./output
#include <iostream>

struct Node {
	Node() {}
	Node(int e, Node* n) : elem(e), next(n) {}
	int elem = 0;
	Node* next = nullptr;

};


struct iter {
	Node* ptr;

	iter(Node* p) : ptr(p) {}

	iter& operator++() {
		ptr = ptr->next;
		return *this;
	}

	int& operator*() {
		return ptr->elem;
	}

	bool operator!=(iter& other) {
		return ptr != other.ptr;
	}
};


iter begin(Node& head) {
	return iter(head.next);
}

iter end(Node& head) {
	return iter(nullptr);
}


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

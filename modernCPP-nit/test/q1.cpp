/*
Write move constructor and move assignment operator for Buffer class. 
(Just copy this code into the answer box and add those things that are required - ignore everything else)

struct Buffer {
    char * data = nullptr;
    int size = 0;
}
*/

#include <iostream>


struct Buffer {
    char * data = nullptr;
    int size = 0;

    Buffer() : data(nullptr), size(0) {}

    Buffer(Buffer&& other)
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Buffer& operator=(Buffer&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};




int main () {

    std::cout << "Default constructor" << std::endl;
    Buffer buff1;
    buff1.size = 5;
    buff1.data = new char[buff1.size];
    std::cout << "\tbuff1.size=" << buff1.size << std::endl;


    std::cout << "Move constructor" << std::endl;
    Buffer buff2(std::move(buff1));
    std::cout << "\tbuff2.size=" << buff2.size << std::endl;
    std::cout << "\tbuff1.size=" << buff1.size << std::endl;
    std::cout << "\tbuff1.data=" << static_cast<void*>(buff1.data) << std::endl;


    std::cout << "Move assigment op" << std::endl;
    Buffer buff3;
    buff3 = std::move(buff2);
    std::cout << "\tbuff3.size=" << buff3.size << std::endl;
    std::cout << "\tbuff3.data=" << static_cast<void*>(buff2.data) << std::endl;


    return 0;
}
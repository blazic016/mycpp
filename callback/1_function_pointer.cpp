#include <iostream>

void print_message(const char* message) {
    std::cout << message << std::endl;
}

void execute_callback(void (*callback)(const char*)) {
    callback("Hello, World!");
}

int main() {
    execute_callback(print_message);
    return 0;
}
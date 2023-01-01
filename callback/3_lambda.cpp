#include <iostream>

template <typename Callback>
void execute_callback(Callback callback) {
    callback("Hello, World!");
}

int main() {
    execute_callback([](const char* message) {
        std::cout << message << std::endl;
    });
    return 0;
}
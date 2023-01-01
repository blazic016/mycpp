#include <iostream>

struct PrintMessage {
    void operator()(const char* message) {
        std::cout << message << std::endl;
    }
};

template <typename Callback>
void execute_callback(Callback callback) {
    callback("Hello, World!");
}

int main() {

    PrintMessage print_message;

    execute_callback(print_message);

    return 0;
}
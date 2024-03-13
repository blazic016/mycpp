#include <iostream>
#include <type_traits>
#include <sstream>

template<typename T>
void myprintf(T arg) {
    std::cout << arg;
}

template<typename T, typename... Args>
void myprintf(const char* format, T arg, Args... args) {
    const char* ptr = format;
    // std::cout << "format=" << format << "arg="<<arg << std::endl;
    // std::cout << "Broj argumenata: " << sizeof...(args) + 1 << std::endl;
    while (*ptr != '\0') {
        int fs_cnt = 0;
        if (*ptr == '%' && *(ptr + 1) == 'd') {
            fs_cnt++;
            if ( fs_cnt != int(sizeof...(args) + 1)) {
               std::cerr << "Error: Format specifier and number of args are different! line:" << __LINE__<<"\n";
                return;
            }
            if ((std::is_same<T, int>::value == false) && (fs_cnt == int(sizeof...(args) + 1)) ) {
                std::cerr << "Error: Type mismatch for %d! line:" << __LINE__<<"\n";
                return;
            }
            std::cout << arg;
            ptr += 2; 
        } else if (*ptr == '%' && *(ptr + 1) == 'f') {
            fs_cnt++;
            if ( fs_cnt != int(sizeof...(args) + 1)) {
               std::cerr << "Error: Format specifier and number of args are different! line:" << __LINE__<<"\n";
                return;
            }
            if (std::is_same<T, float>::value == false) {
                std::cerr << "Error: Type mismatch for %f! line:" << __LINE__<<"\n";
                return;
            }
            std::cout << arg;
            ptr += 2;
        } else if (*ptr == '%' && *(ptr + 1) == 's') {
            fs_cnt++;
            if ( fs_cnt != int(sizeof...(args) + 1)) {
               std::cerr << "Error: Format specifier and number of args are different! line:" << __LINE__<<"\n";
                return;
            }
            if (std::is_same<T, const char*>::value == false) {
                std::cerr << "Error: Type mismatch for %s! line:" << __LINE__<<"\n";
                return;
            }
            std::cout << arg;
            ptr += 2;
        } else {
            std::cout << *ptr;
            ++ptr;
        }
    }
}

int main(int argc, char** argv) {
    myprintf("Hello from string only\n");
    myprintf("int value: %d\n", int(123));
    myprintf("float value: %f\n", float(1.23));
    myprintf("const char *value: %s\n", "123456789");
    
    // THIS IS NOT IMPLEMENTED!
    // myprintf("int value: %d, float value: %f, const char *value: %s\n", int(123), float(1.23), "123456789");

    myprintf("int value: %d\n", "123456789"); // Error
    myprintf("const char *value: %s\n", 123456789); // Error
    myprintf("int value: %d\n", 12345, 6789); // Error
    
    return 0;
}

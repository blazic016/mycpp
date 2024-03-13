Task 1
Write function template sum that sums all the arguments. Write the code in file exercise1.cpp.

Task 2
Write function template min that returns the smallest of all its arguments. Write the code in file exercise2.cpp.

Task 3 - Optional
Write function template my_printf which performs printing to standard output like C library function printf, but it should perform verification that types expected by the format string match types of the actual arguments. Limit implementation to only %d, %f, %s. Write the code in file exercise3.cpp Download exercise3.cpp(found in Labs/Lab06).
- exercise3.cpp
```
#include <iostream>
#include <type_traits>


// ToDo: Implement myprintf fn

int main(int argc, char** argv) 
{
	myprintf("Hello from string only\n");
	myprintf("int value: %d\n", 123);
	myprintf("float value: %f\n", 1.23);	
	myprintf("const char *value: %s\n", "123456789");	
	myprintf("int value: %d, float value: %f, const char *value: %s\n", 123, 1.23, "123456789");
	
	myprintf("int value: %d\n", "123456789"); // Error
	myprintf("const char *value: %s\n", 123456789);	// Error
	myprintf("int value: %d\n", 12345, 6789); // Error
	
    return 0;
}
```
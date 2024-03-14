

// The function **foo** accesses the global shared variable **x**. 
// Add code to the function foo so that access to the variable **x** is protected by mutex **m**.
// (Copy the code into the answer box and modify it according to the task)

#include<iostream>
#include <mutex>


std::mutex m;
int x;

void foo() {
    std::lock_guard<std::mutex> guard(m);
    x += 1;
}


int main () {
    foo();
    return 0;
}

/*
Write function foo that accepts parameter n of type int and returns the sum of the first n natural numbers.
This function should be written so that the following code compilers:

```
constexprt int sum = foo(100);
Value in sum shoud be 5050

and to repport an error when compiling this code:
constexpr int sum1 = foo(-50);
Because negative values are not accepted
```

*/

#include <iostream>
#include <cassert>

constexpr int foo (const int n) {
    static_assert(n > 0, "ERROR: n must be non-negative.");
    int res=0;
    for(int i=0;i<=n;i++)
        res = res+i;
    return res;
}

int main () {
    constexpr int sum = foo(100);
    std::cout << "sum=" << sum << std::endl;
    constexpr int sum1 = foo(-50);
    std::cout << "sum1=" << sum1 << std::endl;
    return 0;
}
#include <iostream>

auto add(int a, int b) -> int {
    std::cout << "add called with a = " << a << ", b = " << b << std::endl;
    return a + b;
}
auto sub(int& a) -> int {
    std::cout << "sub called with a = " << a << std::endl;
    a--;
    return a;
}

auto main() -> int {
    int a = 5;
    if (a) {
        std::cout << "a is test" << std::endl;
    };

    int b = add(sub(a), sub(a));
    std::cout << "b is " << b << std::endl;
    std::cout << "a is " << a << std::endl;
    return 0;
}

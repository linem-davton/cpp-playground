#include <iostream>

auto main() -> int {
    // Bit shifts
    int x = 3;  // 0011
    while (x != -1) {
        std::cout << "Enter a number: ";
        std::cin >> x;
        std::cout << "x<<2: " << (x << 2) << '\n';  // multiply by 2^2
        std::cout << "x>>2: " << (x >> 2) << '\n';  // Integer divide by 2^2
        std::cout << "x/4: " << (x / 4) << '\n';    // Division by 4
        std::cout << "~x: " << (~x) << '\n';        // Check if x is odd
    }
    return 0;
}

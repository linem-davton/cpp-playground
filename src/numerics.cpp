#include <iostream>
#include <numeric>

auto gcd(int a, int b) -> int {
    if (b == 0) {
        return std::abs(a);
    }
    return gcd(b, a % b);
}

auto lcm(int a, int b) -> int { return std::abs(a) * std::abs(b) / gcd(a, b); }
auto main() -> int {
    std::cout << std::gcd(-24, -36) << std::endl;
    std::cout << std::lcm(-24, 36) << std::endl;
    std::cout << std::gcd(-24, 0) << std::endl;
    std::cout << std::gcd(24, 1) << std::endl;
    std::cout << std::lcm(24, 0) << std::endl;
    std::cout << std::gcd(-24, 1) << std::endl;
    std::cout << gcd(-24, -36) << std::endl;
    std::cout << gcd(24, -2) << std::endl;
    std::cout << lcm(-24, 36) << std::endl;
    return 0;
}

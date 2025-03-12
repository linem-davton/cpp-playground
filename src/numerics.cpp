#include <iostream>
#include <numeric>

/* GCD of two numbers
    Euclidean algorithm
    gcd(a, b) = gcd(b, a % b)
    gcd(a, 0) = |a|
Background: Every divsior of a, b also divides linear combination of a,b
            gcd(a,b) is divsible by all divisors of a,b (lcm of all divisors)
            a mod b = a - bq (linear combination of a,b)
*/
auto gcd(int a, int b) -> int {
    if (b == 0) {
        return std::abs(a);
    }
    return gcd(b, a % b);
}

/* Expressing GCD as a linear combination of a and b
    Extended Euclidean algorithm
    a*x + b*y = gcd(a, b)
    a*x1 + b*y1 = gcd(b, r0) = b*x1 + r0*y1 = b*x1 + (a - b*q0)y1 = a*y1 + b(x1 - q0*y1)

Background:
  gcd(a,b) = smallest positive linear combination of a,b
  Not Unique: x = x1 + k.b/gcd(a,b), y = y1 - k.a/gcd(a,b) for any integer k, where x1, y1 one of the solutions are the solutions
*/

auto gcdExtended(int a, int b, int &x, int &y) -> int {
    // Base case
    if (b == 0) {
        x = 1;  // Has to be 1 for the formula to hold  (gcd(a, 0) = a = a*1 + 0*y)
        y = 7;  // Any integer will result in valid linear combination. 0 is chosen for simplicity
        return a;
    }

    int x1 = 0;
    int y1 = 0;

    // Recursive call
    int gcd = gcdExtended(b, a % b, x1, y1);

    // Back substitution
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

/* LCM of two numbers
    lcm(a, b) = |a| * |b| / gcd(a, b)

    Background: lcm(a,b) = smallest positive number that is divisible by both a and b
    The formula does not generalize to more than two numbers
*/
auto lcm(int a, int b) -> int { return std::abs(a) * std::abs(b) / gcd(a, b); }

auto main() -> int {
    std::cout << std::lcm(-24, 36) << std::endl;
    std::cout << std::gcd(-24, 0) << std::endl;
    std::cout << std::gcd(24, 1) << std::endl;

    int x, y = 0;
    int a, b = 0;
    std::cout << "Enter values of a and b: \n";
    std::cin >> a >> b;
    auto gcd_v = gcdExtended(a, b, x, y);
    std::cout << "gcd: " << gcd_v << " x: " << x << " y: " << y << " ax + by = " << a * x + b * y << std::endl;
    return 0;
}

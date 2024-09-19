#include <iostream>

constexpr auto fib(int n) -> int {
  if (n <= 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

auto main() -> int {
  const int n = 10;
  constexpr int result = fib(n);
  std::cout << "fib(" << n << ") = " << result << "\n";
  return 0;
}

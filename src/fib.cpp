#include <iostream>

int fib(int n) {
  if (n <= 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

int main() {
  int n = 10;
  std::cout << "fib(" << n << ") = " << fib(n) << "\n";
  return 0;
}

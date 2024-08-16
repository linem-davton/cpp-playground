#include <iostream>

#define max(a, b) a > b ? a : b

auto main() -> int {
  int a = 5, b = 10;
  auto c = max(a, --b);
  std::cout << c << std::endl;
  return 0;
}

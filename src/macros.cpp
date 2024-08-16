#include <iostream>

#define max(a, b) a > b ? a : b
#define mult(a, b) a *b

auto main() -> int {
  int a = 12, b = 10;
  auto c = max(a, --b);
  std::cout << c << " " << b
            << "\n"; // --b is evaluated potentially twice and atleast once

  int d = 2, e = 3;
  c = mult(d + 1, e); // 2 + 1 * 3, not 3 * 3
  std::cout << c << "\n";
  return 0;
}

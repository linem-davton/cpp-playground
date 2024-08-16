#include <iostream>
//
// the following macro is not safe, when a and b are expressions,
// beacuse of operator precedence, the macro will not work as expected
#define i_max(a, b) a > b ? a : b
#define i_mult(a, b) a *b

// right way to do it is to wrap the arguments in parantheses
#define max(a, b) ((a) > (b) ? (a) : (b))
#define mult(a, b) (a) * (b)

#define PRINT(x) std::cout << "value of " << #x << " " << x << "\n"

auto main() -> int {
  int a = 12, b = 10;
  auto c = max(a, --b);
  std::cout << "max(a, --b) " << c << " b " << b
            << "\n"; // --b is evaluated potentially twice and atleast once

  int d = 2, e = 3;
  auto i_c = i_mult(d + 1, e); // 2 + 1 * 3 = 5, not 3 * 3 = 9
  auto c_c = mult(d + 1, e);   // 3 * 3
  std::cout << "i_mult " << i_c << "\n";
  std::cout << "mult " << c_c << "\n";
  PRINT(i_c);
  int j = 2 * (d = 10);
  PRINT(j);
  PRINT(d);
  return 0;
}

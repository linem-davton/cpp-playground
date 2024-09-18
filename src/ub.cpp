#include <iostream>

int main() {
  int i = 1;
  std::cout << "Before" << std::endl;
  while (i) {
  }
  std::cout << "After - Should never print" << std::endl;
}

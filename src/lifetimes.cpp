#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>

// void take(const Tracker&) { std::cout << "take(const Tracker&)\n"; }

// void take(Tracker&&) { std::cout << "take(Tracker&&)\n"; }

struct Base {
    int val{0};
    int aval;
    Base() { std::cout << "Base\n"; }
    Base(int val) : val(val) { std::cout << "Base int\n"; }
};
struct Member1 {
    int val;
    Member1() { std::cout << "Member1\n"; }
    Member1(int val) : val(val) { std::cout << "Member1 int\n"; }
};
struct Member2 {
    int val;
    Member2() { std::cout << "Member2\n"; }
    Member2(int val) : val(val) { std::cout << "Member2 int\n"; }
};
struct Derived : Base {
    Member1 m1{2};
    Member2 m2{3};
    Derived() : m1(10) { std::cout << "Derived\n"; }
};

extern "C" void foo(int);
void foo(double) { std::cout << "double"; };  // This is a C++ function

auto main() -> int {
    // std::cout << 25u - 50 << "\n";
    // unsigned int s = 0;
    // std::cout << --s << "\n";  // Underflow!
    //
    // int i = 69;
    // float& f = reinterpret_cast<float&>(i);
    // char* c = reinterpret_cast<char*>(&i);
    // std::cout << i << " " << f << " " << *c << "\n";
    // std::cout << std::pow(2, 8) - 1 << "\n";
    //
    // take({2});                // Line F
    // take(t3);                 // Line G
    // take(Tracker{3});         // Line H
    //
    // const Tracker& ref1 = Tracker{4};  // Line I
    // Tracker&& ref2 = Tracker{5};       // Line J
    // Tracker& ref3 = Tracker{6};        // Line K — valid?
}

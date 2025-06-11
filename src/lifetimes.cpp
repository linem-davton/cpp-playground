#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>

struct Tracker {
    Tracker() { std::cout << "Default ctor\n"; }
    Tracker(int) { std::cout << "Tracker(int)\n"; }
    Tracker(std::initializer_list<int>) { std::cout << "Tracker(init_list)\n"; }
    explicit Tracker(double) { std::cout << "Tracker(double)\n"; }
    explicit Tracker(int, double) { std::cout << "Double ints \n"; }
    Tracker(const Tracker&) { std::cout << "Copy ctor\n"; }
    Tracker(Tracker&&) { std::cout << "Move ctor\n"; }
    ~Tracker() { std::cout << "~Tracker()\n"; }
};

void take(Tracker) { std::cout << "take(Tracker by value)\n"; }

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
    Tracker&& t1 = Tracker();  // Rvalue reference to a temporary
    std::cout << "Tracker&& t1 created\n";
    const Tracker& t2 = t1;  // Calls the copy constructor
    const Tracker& t3 = t2;  // Calls the copy constructor

    take(t3);  // Calls take(Tracker by value)
    std::cout << "Exiting main\n";
    return 0;
}

// int main() { Derived d;
//   std::cout<<d.val<<" "<<d.m1.val<<" "<<d.m2.val<<"\n";}
// int main() {
//     Tracker t1 = {1};         // Line A
//     Tracker t2{1};            // Line B
//     Tracker t3(1);            // Line C
//     //Tracker t4 = {1.1};       // Line D
//     Tracker t5(1.1);          // Line E
//     Tracker t6 = 2;
//     Tracker t7 = 2.3;
//     Tracker t8 (2,3);
//     Tracker t9{2,3};
//     Tracker t10 = {2,3};
//
//     std::cout<< 25u - 50 <<"\n";
//     unsigned int s = 0;
//     std::cout<< --s <<"\n"; // Underflow!
//
//   int i = 69;
//   float& f = reinterpret_cast<float&>(i);
//   char* c = reinterpret_cast<char*>(&i);
//   std::cout<<i<<" "<<f<<" "<<*c<< "\n";
//   std::cout<<std::pow(2,8)-1<<"\n";
//
//     // take({2});                // Line F
//     // take(t3);                 // Line G
//     // take(Tracker{3});         // Line H
//     //
//     // const Tracker& ref1 = Tracker{4};  // Line I
//     // Tracker&& ref2 = Tracker{5};       // Line J
//     // Tracker& ref3 = Tracker{6};        // Line K — valid?
// }
//

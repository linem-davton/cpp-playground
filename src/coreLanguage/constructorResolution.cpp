#include <cmath>
#include <initializer_list>
#include <iostream>

// Constructor Resolution And Initialization Lists
struct Tracker {
    Tracker() { std::cout << "Default ctor\n"; }

    Tracker(int) { std::cout << "Tracker(int)\n"; }
    Tracker(std::initializer_list<int>) { std::cout << "Tracker(init_list)\n"; }

    explicit Tracker(double) { std::cout << "Tracker(double)\n"; }
    explicit Tracker(int, double) { std::cout << "Double ints \n"; }

    // --- Copy and move constructors ---
    Tracker(const Tracker&) { std::cout << "Copy ctor\n"; }
    Tracker(Tracker&&) { std::cout << "Move ctor\n"; }

    ~Tracker() { std::cout << "~Tracker()\n"; }
};

auto main() -> int {
    Tracker t1 = {1};  // Calls Tracker(initializer_list<int>) constructor
    Tracker t2{1};     // Calls Tracker(initializer_list<int>) constructor
    Tracker t3(1);     // (), disables initializer_list constructor, calls Tracker(int) constructor
    // Tracker t4 = {1.1};  // Tries to call Tracker(initializer_list<int>), but raises narrow conversion warning
    //  Tracker t4{1.1};     // Tries to call Tracker(initializer_list<int>), but raises narrow conversion warning
    Tracker t5(1.1);   // Calls Tracker(double) constructor, explicit conversion from double to Tracker
    Tracker t6 = 2;    // Calls Tracker(int) constructor, implicit conversion from int to Tracker
    Tracker t7 = 2.3;  // Calls Tracker(int), does not raise a Warning!

    Tracker t8(2, 3);      // Calls Tracker(int, double) constructor, explicit conversion from int and double to Tracker
    Tracker t9{2, 3};      // Calls Tracker(initializer_list<int>) constructor, as it matches better than Tracker(int, double)
    Tracker t10 = {2, 3};  // Calls Tracker(initializer_list<int>) constructor, as it matches better than Tracker(int, double)
}

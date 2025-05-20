#include<iostream>

struct Tracker {
    Tracker() { std::cout << "Default ctor\n"; }
    Tracker(int) { std::cout << "Tracker(int)\n"; }
    Tracker(std::initializer_list<int>) { std::cout << "Tracker(init_list)\n"; }
    explicit Tracker(double) { std::cout << "Tracker(double)\n"; }
    explicit Tracker(int, double){std::cout<<"Double ints \n";}
    Tracker(const Tracker&) { std::cout << "Copy ctor\n"; }
    Tracker(Tracker&&) { std::cout << "Move ctor\n"; }
    ~Tracker() { std::cout << "~Tracker()\n"; }
};



void testfunc(Tracker){
  std::cout<<"By value \n";
} // T is destroyed here 
/* Uncomment the Following Functions to get compiler error due to failed function resolution*/

// void testfunc(Tracker&){
//   std::cout<<"By lavlue ref \n";
// }
//
// void testfunc(const Tracker&){
//   std::cout<<"By const ref \n";
// }
//
//  void testfunc(Tracker&& ){
//    std::cout<<"By rvalue ref \n";
// }
//
auto main() -> int{
  Tracker t;
  testfunc(t);
  testfunc(std::move(t));
  return 0;
}

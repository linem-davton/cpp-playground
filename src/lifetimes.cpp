#include <iostream>

struct S {
    S() { std::cout << "ctor\n"; }
    S(S&&) { std::cout << "move\n"; }
    ~S() { std::cout << "dtor\n"; }
};

S makeS() {
    return S(); // returns a prvalue
}

int main() {
    S s = std::move(makeS()); // disables RVO
}


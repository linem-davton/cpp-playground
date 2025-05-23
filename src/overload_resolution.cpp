#include <iostream>
#include <vector>
#include <memory>

struct Logger {
    Logger() { std::cout << "Logger constructed\n"; }
    Logger(const Logger&) { std::cout << "Logger copied\n"; }
    Logger(Logger&&) { std::cout << "Logger moved\n"; }
    ~Logger() { std::cout << "Logger destructed\n"; }
};

struct Resource {
    std::shared_ptr<Logger> logger;
    int* data;
    size_t size;
    
    Resource(size_t sz) : logger(std::make_shared<Logger>()), data(new int[sz]), size(sz) {
        std::cout << "Resource constructed with size " << sz << "\n";
    }
    ~Resource() {
        delete[] data;
        std::cout << "Resource destructed\n";
    }
    
    // Rule of Five: Only copy constructor explicitly implemented!
    Resource(const Resource& other)
        : logger(other.logger), size(other.size)
    {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::cout << "Resource copied\n";
    }
  Resource(Resource&& other): logger(std::move(other.logger)), data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
    std::cout<<"Resource moved\n";

  }
};

Resource make_resource(int n) {
    Resource r(n);
    return r;
}

struct M {
    ~M() { std::cout << "M dtor\n"; }
};
struct S {
    M m;
    ~S() { std::cout << "S dtor\n"; }
};


int main() {
    // S s;
    // std::vector<Resource> vec;
    // vec.reserve(2);
    // vec.push_back(make_resource(3)); // Push_back() can take rvalue reference, and call move constructor if it exits, otherwise copy
    // vec.push_back(vec[0]);
    int* p = new int(5);
    int& k = *p;
    std::cout<<"k:" << k<<" *p:"<<*p <<"\n";
    delete p;
    std::cout<<"k:" << k<<" *p "<<*p <<"\n";
    return 0;
}


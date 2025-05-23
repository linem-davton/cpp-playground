#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

struct S {
    double d;
    // char pad[56]; // Uncomment to mitigate (assuming 64-byte cache line)
};

int main() {
    constexpr size_t N = 1024 * 1024;
    std::vector<S> arr(2);

    auto worker = [&](int idx) {
        for (size_t i = 0; i < N; ++i) {
            arr[idx].d += 1.0;
        }
    };

    std::thread t1(worker, 0);
    std::thread t2(worker, 1);

    t1.join();
    t2.join();

    std::cout << arr[0].d << ' ' << arr[1].d << '\n';
}

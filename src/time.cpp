#include <chrono>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <thread>

template <typename Clock>
concept is_clock = requires {
    typename Clock::duration;
    typename Clock::time_point;
    { Clock::now() } -> std::convertible_to<typename Clock::time_point>;
};

template <is_clock clock>
void measure_precision() {
    auto last = clock::now();
    std::set<std::chrono::nanoseconds> deltas;

    for (int i = 0; i < 1'000'000; ++i) {
        auto now = clock::now();
        auto diff = now - last;
        deltas.insert(std::chrono::duration_cast<std::chrono::nanoseconds>(diff));
        last = now;
    }

    std::cout << "Unique deltas seen: " << deltas.size() << "\n";
    if (deltas.size() > 0) {
        auto min_delta = *deltas.begin();
        auto max_delta = *deltas.rbegin();
        std::cout << "Min delta: " << min_delta.count() << " ns\n";
        std::cout << "Max delta: " << max_delta.count() << " ns\n";
    }
}

template <is_clock Clock>
void measure_precision2() {
    using namespace std::chrono;
    auto now = Clock::now();
    typename Clock::time_point prev;
    do {
        prev = now;
        now = Clock::now();
    } while (now == prev);

    std::cout << "Observed resolution: " << std::chrono::duration_cast<std::chrono::nanoseconds>(now - prev).count() << " ns\n";
}
template <typename Clock>
void print_clock_info(const std::string& name) {
    using namespace std::chrono;
    std::cout << "Clock: " << name << "\n";
    std::cout << " - Is steady: " << std::boolalpha << Clock::is_steady << "\n";

    using Period = typename Clock::period;
    std::cout << " - Tick period: " << Period::num << "/" << Period::den << " seconds\n";

    double seconds_per_tick = static_cast<double>(Period::num) / Period::den;
    std::cout << " - Seconds per tick: " << seconds_per_tick << "\n";
    std::cout << " - Precision: " << (1.0 / seconds_per_tick) << " ticks/sec\n";
    std::cout << "\n";
}

void sleep_for_seconds(std::chrono::nanoseconds time) {
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(time);
    auto end = std::chrono::steady_clock::now();
    std::cout << duration_cast<std::chrono::microseconds>(end - start).count() << "\n";  // might be 10,000–100,000 ns
}

auto main() -> int {
    measure_precision<std::chrono::system_clock>();
    measure_precision<std::chrono::steady_clock>();
    measure_precision<std::chrono::high_resolution_clock>();

    namespace fs = std::filesystem;
    using namespace std::chrono_literals;
    print_clock_info<std::chrono::system_clock>("system_clock");
    print_clock_info<std::chrono::steady_clock>("steady_clock");
    print_clock_info<std::chrono::high_resolution_clock>("high_resolution_clock");
    print_clock_info<fs::file_time_type::clock>("file_time_type::clock");
    sleep_for_seconds(10ns);
    return 0;
}

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>
#include "array_utils.h"
class SparseTable {
    std::vector<std::vector<int>> table;

   public:
    SparseTable(const std::vector<int>& data) {
        // Build min 2D table, size of table (data.size(), j)
        table.resize(data.size());
        if (!data.size()) throw("Invalid arguments");
        int j = std::floor(std::log2(data.size()));

        for (size_t i = 0; i < data.size(); i++) {
            table[i].push_back(data[i]);
        }
        for (int k = 1; k <= j; k++) {
            for (size_t i = 0; i + (1 << k) <= data.size(); i++) {
                table[i].push_back(std::min(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]));
            }
        }
    }
    auto query(int l, int r) -> int {  // l and r inclusive
        if (l > r) throw("Invalid arguments");
        // length of range
        int size = r - l + 1;
        int k = std::floor(std::log2(size));
        // Divide the range (l,r) one starting at l, and another that ends at r.
        return std::min(table[l][k], table[r - (1 << k) + 1][k]);
    }

    void print() {
        std::cout << "Sparse Table:" << table.size() << "\n";
        for (const auto& vec : table) {
            for (const auto& e : vec) {
                std::cout << e << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::vector<int> h{7, 1, 7, 2, 2, 4};
    SparseTable table(h);
    int max = 0;
    int l = 0;
    int r = h.size() - 1;
    table.print();
    while (l <= r) {
        int min = table.query(l, r);
        int area = min * (r - l + 1);
        max = std::max(max, area);
        // Compare the l, r and drop the lowest
        std::cout << l << " " << r << " " << min << " " << area << "\n";
        if (h[l] < h[r]) {
            l++;
        } else {
            r--;
        }
    }

    std::cout << max << "\n";
    return 0;
}

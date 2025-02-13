//

// Takes map[Str:Freq] as input and returns map[Str:Code] as output,
//

#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using FrequencyTable = std::unordered_map<std::string, int>;
using HuffmanCodeTable = std::unordered_map<std::string, std::string>;
using FrequencyPair = std::pair<std::string, int>;
using CodePair = std::pair<std::string, std::string>;
class TreeNode {
   public:
    TreeNode(FrequencyPair val) : val(std::move(val)){};

    auto operator==(const TreeNode& other) const -> bool { return this->val.first == other.val.first; }
    TreeNode* parent{nullptr};  // non owning pointer, just for reference.
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    FrequencyPair val;
    std::string code;
};

using Tree = std::vector<std::unique_ptr<TreeNode>>;
auto find_two_smallest(const Tree& input) -> std::pair<int, int> {
    int smallest = INT_MAX;
    int second_smallest = INT_MAX;
    int smallest_index = -1;
    int second_smallest_index = -1;
    // Find root nodes smallest
    for (std::size_t i = 0; i < input.size(); i++) {
        if (input[i]->parent == nullptr && input[i]->val.second < smallest) {
            smallest = input[i]->val.second;
            smallest_index = i;
        }
    }

    // Find root nodes smallest
    for (std::size_t i = 0; i < input.size(); i++) {
        if ((input[i]->parent == nullptr) && (input[i]->val.second < second_smallest) && (input[i] != input[smallest_index])) {
            second_smallest = input[i]->val.second;
            second_smallest_index = i;
        }
    }

    return std::pair<int, int>{smallest_index, second_smallest_index};
}

void breadth_first_transversal(const TreeNode* root, HuffmanCodeTable& out) {
    // Base Case: NO childeren
    if ((root->left == nullptr) && (root->right == nullptr)) {
        out[root->val.first] = root->code;
    }

    // Explore all choices: Left and right
    if (root->left != nullptr) {
        root->left->code = root->code + "0";
        breadth_first_transversal(root->left, out);
    }
    if (root->right != nullptr) {
        root->right->code = root->code + "1";
        breadth_first_transversal(root->right, out);
    }
}

auto gen_code(const Tree& tree) -> HuffmanCodeTable {
    // Root node is pushed last into the vector, just happens to be the case.
    auto* root = tree.back().get();
    HuffmanCodeTable out;
    breadth_first_transversal(root, out);
    return out;
}

auto huffman(FrequencyTable input) -> HuffmanCodeTable {
    // std::size_t symbols = input.size();
    Tree tree;
    // Go through the input, in shorted order, lowest FrequcyFist, and append it to the tree
    // I have a map of str::int, find the smallest str::int manually
    //
    for (const auto& elem : input) {
        tree.emplace_back(std::make_unique<TreeNode>(elem));
    }

    while (true) {
        auto two_smallest = find_two_smallest(tree);
        auto smallest = two_smallest.first;
        auto second_smallest = two_smallest.second;
        if (smallest == -1 || second_smallest == -1) {
            break;
        }
        std::cout << "Smallest " << tree[smallest]->val.first << " " << "Second Smallest " << tree[second_smallest]->val.first << "\n";

        // Create a new node in the input
        auto total_count = tree[smallest]->val.second + tree[second_smallest]->val.second;
        auto label = tree[smallest]->val.first + tree[second_smallest]->val.first;

        // Create a new Tree node
        FrequencyPair new_node_val{label, total_count};
        auto new_node_ptr = std::make_unique<TreeNode>(new_node_val);
        new_node_ptr->left = tree[smallest].get();
        new_node_ptr->right = tree[second_smallest].get();
        tree[smallest]->parent = new_node_ptr.get();
        tree[second_smallest]->parent = new_node_ptr.get();
        tree.push_back(std::move(new_node_ptr));
    }
    for (const auto& elem : tree) {
        std::cout << "Tree Element: " << elem->val.first << " : " << elem->val.second << "\n";
    }
    // build the code transerving the tree,
    auto output = gen_code(tree);
    return output;
}

auto main() -> int {
    FrequencyTable input{{"A", 2}, {"B", 3}, {"C", 4}, {"D", 6}};
    auto out = huffman(input);
    for (const auto& pair : out) {
        std::cout << pair.first << " : " << pair.second << "\n";
    }
}

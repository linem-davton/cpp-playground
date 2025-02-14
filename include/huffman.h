#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using FrequencyTable = std::unordered_map<std::string, int>;
using HuffmanCodeTable = std::map<std::string, std::string>;
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
auto find_two_smallest(const Tree& input) -> std::pair<int, int>;

void depth_first_transversal(const TreeNode* root, HuffmanCodeTable& out);
auto huffman(const FrequencyTable& input) -> HuffmanCodeTable;

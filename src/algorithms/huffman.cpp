#include "huffman.h"
#include "utils.h"

auto find_two_smallest(const Tree& input) -> std::pair<int, int> {
    int smallest = INT_MAX;
    int second_smallest = INT_MAX;
    int smallest_index = -1;
    int second_smallest_index = -1;
    // Find root nodes smallest
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i]->parent == nullptr && input[i]->val.second < smallest) {
            smallest = input[i]->val.second;
            smallest_index = i;
        }
    }

    // Find root nodes smallest
    for (int i = 0; i < (int)input.size(); i++) {
        if ((input[i]->parent == nullptr) && (input[i]->val.second < second_smallest) && (input[i] != input[smallest_index])) {
            second_smallest = input[i]->val.second;
            second_smallest_index = i;
        }
    }

    return std::pair<int, int>{smallest_index, second_smallest_index};
}

void depth_first_transversal(const TreeNode* root, HuffmanCodeTable& out) {
    // Base Case: No childeren
    if ((root->left == nullptr) && (root->right == nullptr)) {
        out[root->val.first] = root->code;
    }

    // Explore all choices: Left and right
    if (root->left != nullptr) {
        root->left->code = root->code + "0";
        depth_first_transversal(root->left, out);
    }
    if (root->right != nullptr) {
        root->right->code = root->code + "1";
        depth_first_transversal(root->right, out);
    }
}

auto huffman(const FrequencyTable& input) -> HuffmanCodeTable {
    Tree tree;
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

    auto* root = tree.back().get();
    HuffmanCodeTable out;
    depth_first_transversal(root, out);
    return out;
}

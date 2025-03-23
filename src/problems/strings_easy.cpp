#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "utils.h"
/* Anagram: A word or phrase that is formed by rearranging the letters of another word or phrase.
 * For example, "listen" is an anagram of "silent".
 * Given two strings s and t, write a function to determine if t is an anagram of s.
 *
 * Solution:
 * 1. Sorting: Sort both strings and compare them. If they are equal, then they are anagrams.
 *    Time Complexity: O(nlogn+mlogm) where n is the length of s and m is the length of t.
 *    Space Complexity: O(1)
 * 2. Hash Map:
 *  Parse both strings and count the occurence of each alphabet. If the maps are the same, then they are anagrams.
 *    Space Complexity: O(n + m) where n,m is the length of s and t.
 */
auto isAnagram(std::string s, std::string t) -> bool {
    // Both strings must have same set of characters and same length
    if (s.size() != t.size()) {
        return false;
    }
    // sorted strings must be the same, else not anagram
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

auto isAnagram_map(std::string s, std::string t) -> bool {
    // Both strings must have same set of characters and same length
    if (s.size() != t.size()) {
        return false;
    }
    // parse both string and count the occurence of alphabet and, the map should be the same.
    std::unordered_map<char, unsigned int> s_;
    std::unordered_map<char, unsigned int> t_;

    for (std::size_t i = 0; i < std::min(s.size(), t.size()); i++) {
        s_[s[i]]++;
        t_[t[i]]++;
    }
    return s_ == t_;
}

void genstring(std::vector<std::string>& vec, int n, std::string& s, int f, int b) {
    // Base conditions
    if ((int)s.size() == 2 * n) {
        std::cout << "s: " << s << " f: " << f << " b: " << b << std::endl;
        vec.push_back(s);
        return;
    }
    // Explore all choices
    if (f > b) {  // max f = n, max b = n
        s.append(")");
        genstring(vec, n, s, f, ++b);
        s.pop_back();
        --b;
    }
    if (f < n) {
        s.append("(");
        genstring(vec, n, s, ++f, b);
        s.pop_back();
        --f;
    }
}
auto generateParenthesis(int n) -> std::vector<std::string> {
    std::vector<std::string> vec;
    std::string s;
    genstring(vec, n, s, 0, 0);
    return vec;
}

auto main() -> int {
    std::string s = "racecar";
    std::string t = "carrace";
    std::cout << "Is Anagram: " << isAnagram(s, t) << std::endl;
    std::vector<std::string> str = generateParenthesis(5);
    printVec(str);
    std::cout << "Size: " << str.size() << "\n";
    return 0;
}

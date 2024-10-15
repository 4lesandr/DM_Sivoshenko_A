#include "trie.h"
#include <iostream>

Trie::Trie() : root(std::unique_ptr<TrieNode>(new TrieNode())) {}

int Trie::findLongestMatch(const std::string& input, size_t start, size_t& length) {
    TrieNode* node = root.get();
    int last_index = 0;
    length = 0;
    size_t i = start;

    while (i < input.size()) {
        auto it = node->children.find(input[i]);
        if (it == node->children.end()) {
            break;
        }

        node = it->second.get();
        last_index = node->index;
        ++length;
        ++i;
    }

    return last_index;
}

void Trie::insert(const std::string& word, int index) {
    TrieNode* node = root.get();
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = std::unique_ptr<TrieNode>(new TrieNode());
        }
        node = node->children[c].get();
    }
    node->index = index;
}

void Trie::printTrie() const {
    printTrieHelper(root.get(), "");
}

void Trie::printTrieHelper(const TrieNode* node, const std::string& prefix) const {
    if (node->index != 0) {
        std::cout << "'" << prefix << "' -> Index: " << node->index << std::endl;
    }
    for (const auto& child : node->children) {
        printTrieHelper(child.second.get(), prefix + child.first);
    }
}
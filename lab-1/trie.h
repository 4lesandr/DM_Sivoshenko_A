#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <memory>
#include "trie_node.h"

class Trie {
public:
    Trie();
    int findLongestMatch(const std::string& input, size_t start, size_t& length);
    void insert(const std::string& word, int index);
    void printTrie() const;  // Добавленный метод для печати Trie

private:
    std::unique_ptr<TrieNode> root;
    void printTrieHelper(const TrieNode* node, const std::string& prefix) const;
};

#endif // TRIE_H
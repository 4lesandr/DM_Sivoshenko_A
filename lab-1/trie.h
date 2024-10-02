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

private:
    std::unique_ptr<TrieNode> root;
};

#endif // TRIE_H
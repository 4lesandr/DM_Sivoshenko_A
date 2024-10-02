#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <unordered_map>
#include <memory>

class TrieNode {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    int index;

    TrieNode() : index(0) {}
};

#endif // TRIE_NODE_H
#include "compressor.h"
#include "trie.h"
#include <iostream>

void compress(const std::string& input, std::vector<std::pair<int, char>>& compressed_data) {
    Trie trie;
    size_t length = 0;
    int dictionary_index = 0;

    trie.insert("", ++dictionary_index);  
    for (size_t k = 0; k < input.size();) {
        int p = trie.findLongestMatch(input, k, length);
        char next_char = (k + length < input.size()) ? input[k + length] : '\0';
       
        compressed_data.push_back({p == 0 ? 0 : p - 1, next_char});

        std::cout << "Step " << k << ": Found match with index " << (p == 0 ? 0 : p - 1)
                  << ", next char is '" << next_char << "' results in pair ("
                  << (p == 0 ? 0 : p - 1) << ", " << (next_char ? next_char : ' ') << ")" << std::endl;

        std::string new_entry = input.substr(k, length) + next_char;
        trie.insert(new_entry, ++dictionary_index);

        std::cout << "Inserted new entry '" << new_entry << "' into Trie." << std::endl << std::endl;

        trie.printTrie();
        std::cout << std::endl;

        k += length + 1;
    }
}
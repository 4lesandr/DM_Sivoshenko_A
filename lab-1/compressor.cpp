#include "compressor.h"
#include "trie.h"

void compress(const std::string& input, std::vector<std::pair<int, char>>& compressed_data) {
    Trie trie;
    size_t length = 0;
    int dictionary_index = 0;

    trie.insert("", ++dictionary_index);  

    for (size_t k = 0; k < input.size();) {
        int p = trie.findLongestMatch(input, k, length);
        char next_char = (k + length < input.size()) ? input[k + length] : '\0';

        compressed_data.push_back({p-1, next_char});

        std::string new_entry = input.substr(k, length) + next_char;
        trie.insert(new_entry, ++dictionary_index);

        k += length + 1;
    }
}
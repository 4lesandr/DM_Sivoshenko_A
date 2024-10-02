#include "decompressor.h"

void decompress(const std::vector<std::pair<int, char>>& compressed_data, std::string& output) {
    std::vector<std::string> dictionary;
    dictionary.push_back("");

    for (const auto& record : compressed_data) {
        int p = record.first;
        char q = record.second;

        std::string new_entry = dictionary[p] + q;
        output += new_entry;

        dictionary.push_back(new_entry);
    }
}
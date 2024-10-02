#include "dictionary.h"
#include <iostream>

int findLongestMatch(const std::vector<std::string>& dictionary, const std::string& input, size_t k) {
    size_t l = 0;
    int p = 0;

    for (size_t i = 1; i < dictionary.size(); ++i) {
        size_t m = dictionary[i].length();
        if (input.substr(k, m) == dictionary[i] && m > l) {
            p = i;
            l = m;
        }
    }
    return p;
}

void printDictionary(const std::vector<std::string>& dictionary) {
    std::cout << "Текущий словарь:" << std::endl;
    for (size_t i = 0; i < dictionary.size(); ++i) {
        std::cout << i << ": " << dictionary[i] << std::endl;
    }
    std::cout << std::endl;
}
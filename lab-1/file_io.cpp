#include "file_io.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удается открыть файл: " + filename);
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

void writeCompressedData(const std::string& filename, const std::vector<std::pair<int, char>>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удается открыть файл для записи: " + filename);
    }
    for (const auto& pair : data) {
        file.write(reinterpret_cast<const char*>(&pair.first), sizeof(int));
        file.write(reinterpret_cast<const char*>(&pair.second), sizeof(char));
    }
}

std::vector<std::pair<int, char>> readCompressedData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удается открыть файл: " + filename);
    }
    std::vector<std::pair<int, char>> data;
    int p;
    char q;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(int))) {
        if (!file.read(reinterpret_cast<char*>(&q), sizeof(char))) {
            break;
        }
        data.emplace_back(p, q);
    }
    return data;
}

void writeFile(const std::string& filename, const std::string& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удается открыть файл для записи: " + filename);
    }
    file << data;
}
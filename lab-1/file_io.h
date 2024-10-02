#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>
#include <utility>

std::string readFile(const std::string& filename);
void writeCompressedData(const std::string& filename, const std::vector<std::pair<int, char>>& data);
std::vector<std::pair<int, char>> readCompressedData(const std::string& filename);
void writeFile(const std::string& filename, const std::string& data);

#endif // FILE_IO_H
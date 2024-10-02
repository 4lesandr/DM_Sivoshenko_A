#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>
#include <vector>
#include <utility>

void decompress(const std::vector<std::pair<int, char>>& compressed_data, std::string& output);

#endif // DECOMPRESSOR_H
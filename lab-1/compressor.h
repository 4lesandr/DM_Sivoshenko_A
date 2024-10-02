#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <vector>
#include <utility>

void compress(const std::string& input, std::vector<std::pair<int, char>>& compressed_data);

#endif // COMPRESSOR_H
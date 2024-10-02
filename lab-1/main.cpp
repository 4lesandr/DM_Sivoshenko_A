#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include "compressor.h"
#include "decompressor.h"
#include "file_io.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Использование: " << argv[0] << " <compress|decompress> <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string input_filename = argv[2];
    std::string output_filename = argv[3];

    try {
        if (mode == "compress") {
            std::string input_text = readFile(input_filename);

            auto start_compress = std::chrono::high_resolution_clock::now();

            std::vector<std::pair<int, char>> compressed_data;
            compress(input_text, compressed_data);

            auto end_compress = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> compress_duration = end_compress - start_compress;

            writeCompressedData(output_filename, compressed_data);

            std::cout << "Данные успешно сжаты и записаны в " << output_filename << '\n';
            std::cout << "Время сжатия: " << compress_duration.count() << " секунд" << '\n';

        } else if (mode == "decompress") {
            std::vector<std::pair<int, char>> compressed_data = readCompressedData(input_filename);

            auto start_decompress = std::chrono::high_resolution_clock::now();

            std::string decompressed_text;
            decompress(compressed_data, decompressed_text);

            auto end_decompress = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> decompress_duration = end_decompress - start_decompress;

            writeFile(output_filename, decompressed_text);

            std::cout << "Данные успешно распакованы и записаны в " << output_filename << '\n';
            std::cout << "Время распаковки: " << decompress_duration.count() << " секунд" << '\n';
        } else {
            std::cerr << "Неизвестный режим: " << mode << ". Используйте 'compress' или 'decompress'." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

//g++ -std=c++11 -o lz78_compressor main.cpp compressor.cpp decompressor.cpp file_io.cpp trie.cpp
//./lz78_compressor compress in/.txt compressed/.bin
//./lz78_compressor decompress compressed/.bin out/.txt
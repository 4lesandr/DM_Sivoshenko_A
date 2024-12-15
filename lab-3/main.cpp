#include "Graph.h"
#include <iostream>
#include <exception>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    try {
        if (!fs::exists(inputFilename)) {
            std::cerr << "Ошибка: входной файл " << inputFilename << " не существует." << std::endl;
            return 1;
        }

        fs::create_directories(fs::path(outputFilename).parent_path());

        Graph graph;

        if (!graph.loadFromDOT(inputFilename)) {
            std::cerr << "Не удалось загрузить граф из " << inputFilename << std::endl;
            return 1;
        }

        std::string arborescenceResult;
        std::string drevochislenniiResult;

        bool isArborescence = graph.isArborescence(arborescenceResult);
        bool isDrevochislennii = graph.isDrevochislenny(drevochislenniiResult);

        if (isArborescence) {
            std::cout << "Граф из файла " << inputFilename << " является ордеревом." << std::endl;
        } else {
            std::cout << "Граф из файла " << inputFilename << " не является ордеревом: " << arborescenceResult << std::endl;
        }

        if (isDrevochislennii) {
            std::cout << "Граф из файла " << inputFilename << " является древочисленным." << std::endl;
        } else {
            std::cout << "Граф из файла " << inputFilename << " не является древочисленным: " << drevochislenniiResult << std::endl;
        }

        std::string result = arborescenceResult + "\n" + drevochislenniiResult;
        graph.saveResult(outputFilename, result);
        std::cout << "Результат сохранён в " << outputFilename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
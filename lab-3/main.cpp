#include "Graph.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    Graph graph;
    
    try {
        if (!graph.loadFromDOT(inputFilename)) {
            std::cerr << "Не удалось загрузить граф из " << inputFilename << std::endl;
            return 1;
        }

        std::string result;
        if (graph.isArborescence(result)) {
            std::cout << "\nУспешно! " << result << std::endl;
        } else {
            std::cout << "\nАнализ выявил проблемы! " << result << std::endl;
        }

        graph.saveResult(outputFilename, result);
        std::cout << "Результат сохранён в " << outputFilename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
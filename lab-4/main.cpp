#include "Graph.h"
#include <filesystem>
#include <iostream>

int main() {
    std::string directoryPath = "input";
    
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".dot") {
            std::cout << "Обработка файла: " << entry.path().filename() << std::endl;
            Graph graph(entry.path().string());
            graph.greedyColoring();
            
            std::string outputFilePath = "output/" + entry.path().stem().string() + "_output.dot";
            graph.writeColoringToFile(outputFilePath);
            std::cout << "Результаты записаны в: " << outputFilePath << std::endl << std::endl;
        }
    }
    
    return 0;
}
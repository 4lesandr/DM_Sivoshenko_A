#include "Graph.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    Graph graph;
    
    try {
        if (!graph.loadFromDOT(inputFilename)) {
            std::cerr << "Failed to load graph from " << inputFilename << std::endl;
            return 1;
        }

        std::string result;
        if (graph.isArborescence(result)) {
            std::cout << "Graph analysis successful. " << result << std::endl;
        } else {
            std::cerr << "Graph analysis failed. " << result << std::endl;
        }

        graph.saveResult(outputFilename, result);
        std::cout << "Result saved to " << outputFilename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
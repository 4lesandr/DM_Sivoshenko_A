#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

Graph read_graph_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        exit(EXIT_FAILURE);
    }

    Graph graph;
    std::string line;

    while (std::getline(infile, line)) {
        if (line.find("graph") != std::string::npos || line.find("{") != std::string::npos || line.find("}") != std::string::npos) {
            continue;
        }

        std::istringstream iss(line);
        int u, v;
        double weight;
        char dash;
        std::string label;
        
        if (iss >> u >> dash >> dash >> v >> label) {
            size_t start = label.find('"') + 1;
            size_t end = label.find('"', start);
            weight = std::stod(label.substr(start, end - start));

            graph[u].emplace_back(v, weight);
        }
    }

    infile.close();
    return graph;
}

void write_results_to_file(const std::string& filename, const std::vector<double>& T, const std::vector<int>& Pi) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        exit(EXIT_FAILURE);
    }

    outfile << "Distances from source: \n";
    for (size_t i = 0; i < T.size(); ++i) {
        outfile << "Vertex " << i << ": " << T[i] << "\n";
    }

    outfile << "\nPaths (preceding vertex): \n";
    for (size_t i = 0; i < Pi.size(); ++i) {
        outfile << "Vertex " << i << ": " << Pi[i] << "\n";
    }

    outfile.close();
}
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <map>
#include <filesystem>

Graph::Graph(const std::string& filePath) {
    readGraphFromDot(filePath);
}

void Graph::readGraphFromDot(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

        if (line.find("--") != std::string::npos) {
            size_t pos = line.find("--");
            int u = std::stoi(line.substr(0, pos));
            int v = std::stoi(line.substr(pos + 2));
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        } else if (line.find("->") != std::string::npos) {
            size_t pos = line.find("->");
            int u = std::stoi(line.substr(0, pos));
            int v = std::stoi(line.substr(pos + 2));           
            adjList[u].push_back(v);
        }
    }
}

void Graph::greedyColoring() {
    std::vector<int> vertices;
    for (const auto& pair : adjList) {
        vertices.push_back(pair.first);
    }

    std::sort(vertices.begin(), vertices.end(), [this](int v1, int v2) {
       return adjList[v1].size() > adjList[v2].size();
    });

    for (int vertex : vertices) {
        coloring[vertex] = 0;
    }

    int color = 1;

    while (!vertices.empty()) {
        for (auto it = vertices.begin(); it != vertices.end();) {
            int vertex = *it;
            bool canColor = true;

            for (int neighbor : adjList[vertex]) {
                if (coloring[neighbor] == color) {
                    canColor = false;
                    break;
                }
            }

            if (canColor) {
                coloring[vertex] = color;
                it = vertices.erase(it);
            } else {
                ++it;
            }
        }
        ++color;
    }
}

int Graph::getChromaticNumber() const {
    int chromaticNumber = 0;
    for (const auto& pair : coloring) {
        if (pair.second > chromaticNumber) {
            chromaticNumber = pair.second;
        }
    }
    return chromaticNumber;
}

void Graph::writeColoringToFile(const std::string& outputPath) const {
    const std::map<int, std::string> colorMap = {
        {1, "lightsteelblue"},
        {2, "thistle"},
        {3, "lightpink"},
        {4, "peachpuff"},
        {5, "palegreen"},
        {6, "lightsalmon"},
        {7, "lightcoral"},
        {8, "plum"},
        {9, "lightseagreen"},
        {10, "khaki"}
    };

    std::ofstream outFile(outputPath);
    if (!outFile) {
        std::cerr << "Ошибка записи в файл: " << outputPath << std::endl;
        return;
    }

    int chromaticNumber = getChromaticNumber();
    outFile << "// Хроматическое число: " << chromaticNumber << "\n";

    outFile << "graph G {\n";

    for (const auto& pair : coloring) {
        int vertex = pair.first;
        int color = pair.second;
        
        std::string fillColor = colorMap.at((color - 1) % colorMap.size() + 1);
        
        outFile << "    " << vertex << " [style=filled, fillcolor=" << fillColor << "];\n";
    }

    for (const auto& pair : adjList) {
        int u = pair.first;
        for (int v : pair.second) {
            if (u < v) {
                outFile << "    " << u << " -- " << v << ";\n";
            }
        }
    }

    outFile << "}\n";
}
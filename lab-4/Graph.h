#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
public:
    Graph(const std::string& filePath);

    void greedyColoring();

    void writeColoringToFile(const std::string& outputPath) const;

private:
    std::unordered_map<int, std::vector<int>> adjList;
    std::unordered_map<int, int> coloring;

    void readGraphFromDot(const std::string& filePath);

    int getChromaticNumber() const;
};

#endif // GRAPH_H
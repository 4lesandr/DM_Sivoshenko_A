#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;
public:
    bool loadFromDOT(const std::string& filename);
    bool isArborescence(std::string& output) const;
    void saveResult(const std::string& filename, const std::string& result) const;
};

#endif // GRAPH_H
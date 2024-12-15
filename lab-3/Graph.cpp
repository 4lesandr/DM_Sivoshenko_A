#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stdexcept>

bool Graph::loadFromDOT(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
    }

    adjacencyList.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        int start, end;
        char arrow1, arrow2;

        if (lineStream >> start >> arrow1 >> arrow2 >> end && arrow1 == '-' && arrow2 == '>') {
            adjacencyList[start].push_back(end);
            if (adjacencyList.find(end) == adjacencyList.end()) {
                adjacencyList[end] = std::vector<int>();
            }
        }
    }

    file.close();
    return true;
}

bool Graph::isArborescence(std::string& output) const {
    std::unordered_map<int, int> inDegree;
    std::unordered_set<int> allVertices;
    std::string reasons;

    for (const auto& pair : adjacencyList) {
        int u = pair.first;
        allVertices.insert(u);
        for (int v : pair.second) {
            inDegree[v]++;
            allVertices.insert(v);
        }
    }
    std::vector<int> roots;
    for (int v : allVertices) {
        if (inDegree[v] == 0) {
            roots.push_back(v);
        }
    }

    if (roots.size() != 1) {
        reasons = "Некорректный корень или несколько корней. Найдено корней: " + std::to_string(roots.size()) + ". Корни: ";
        for (int root : roots) {
            reasons += std::to_string(root) + " ";
        }
        reasons += "\n";
        output = reasons;
        return false;
    }

    int root = roots[0];

    for (int v : allVertices) {
        if (v != root && inDegree[v] != 1) {
            reasons += "Вершина " + std::to_string(v) + " имеет некорректную полустепень захода.\n";
        }
    }

    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(root);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        auto it = adjacencyList.find(current);
        if (it != adjacencyList.end()) {
            for (int neighbor : it->second) {
                if (!visited.count(neighbor)) {
                    q.push(neighbor);
                }
            }
        }
    }

    for (int v : allVertices) {
        if (!visited.count(v)) {
            reasons += "Вершина " + std::to_string(v) + " недостижима из корня.\n";
        }
    }

    if (!reasons.empty()) {
        output = reasons;
        return false;
    } else {
        output = "Граф является ордеревом.";
        return true;
    }
}

bool Graph::isDrevochislenny(std::string& output) const {
    int vertexCount = adjacencyList.size();
    int edgeCount = 0;

    for (const auto& pair : adjacencyList) {
        edgeCount += pair.second.size();
    }

    if (vertexCount == edgeCount + 1) {
        output = "Граф является древочисленным.";
        return true;
    } else {
        output = "Граф не является древочисленным (V != E + 1).\n";
        return false;
    }
}

void Graph::saveResult(const std::string& filename, const std::string& result) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
    }
    file << result << std::endl;
    file.close();
}
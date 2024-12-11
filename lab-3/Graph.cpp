#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
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
    int edgeCount = 0;
    std::string reasons;

    for (const auto& pair : adjacencyList) {
        int u = pair.first;
        allVertices.insert(u);
        for (int v : pair.second) {
            inDegree[v]++;
            allVertices.insert(v);
            edgeCount++;
        }
    }

    std::vector<int> roots;
    for (int v : allVertices) {
        if (inDegree[v] == 0) {
            roots.push_back(v);
        }
    }

    if (roots.size() != 1) {
        reasons += "Некорректный корень или несколько корней.\n";
    }

    int root = !roots.empty() ? roots[0] : -1;

    for (int v : allVertices) {
        if (v != root && inDegree[v] != 1) {
            reasons += "Вершина " + std::to_string(v) + " имеет некорректную полустепень захода.\n";
        }
    }

    std::unordered_set<int> visited;
    if (root != -1) {
        std::queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

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
    } else {
        reasons += "Отсутствует корень для начала обхода.\n";
    }

    if (visited.size() != allVertices.size()) {
        reasons += "Не все вершины достижимы.\n";
    }

    if (allVertices.size() != edgeCount + 1) {
        reasons += "Граф не является древочисленным (V != E + 1).";
    }

    if (reasons.empty()) {
        output = "Граф является ордеревом.";
        return true;
    } else {
        output = reasons;
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
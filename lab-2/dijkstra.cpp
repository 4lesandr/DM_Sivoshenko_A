#include "dijkstra.h"
#include <queue>
#include <vector>
#include <limits>

using Pair = std::pair<double, int>;

TAndPi dijkstra(const Graph& graph, int source) {
    int p = graph.size();
    std::vector<double> T(p, std::numeric_limits<double>::infinity());
    std::vector<int> Pi(p, -1);
    std::vector<bool> visited(p, false);

    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> priorityQueue;
    
    T[source] = 0;
    priorityQueue.push({0, source});

    while (!priorityQueue.empty()) {
        auto [currentDistance, u] = priorityQueue.top();
        priorityQueue.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (const auto& [v, weight] : graph.at(u)) {
            if (!visited[v]) {
                double newDist = currentDistance + weight;
                if (newDist < T[v]) {
                    T[v] = newDist;
                    Pi[v] = u;
                    priorityQueue.push({newDist, v});
                }
            }
        }
    }

    return {T, Pi};
}
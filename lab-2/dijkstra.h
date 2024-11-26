#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>
#include "graph.h"

using TAndPi = std::pair<std::vector<double>, std::vector<int>>;

TAndPi dijkstra(const Graph& graph, int source);

#endif // DIJKSTRA_H
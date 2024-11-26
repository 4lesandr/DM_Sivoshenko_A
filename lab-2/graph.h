#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using Graph = std::unordered_map<int, std::vector<std::pair<int, double>>>;

Graph read_graph_from_file(const std::string& filename);
void write_results_to_file(const std::string& filename, const std::vector<double>& T, const std::vector<int>& Pi);

#endif // GRAPH_H
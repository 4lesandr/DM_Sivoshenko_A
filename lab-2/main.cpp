#include "graph.h"
#include "dijkstra.h"
#include <iostream>
#include <string>

int main() {
    std::string input_filename, output_filename;
    int source;

    std::cout << "Enter the input filename: ";
    std::cin >> input_filename;

    std::cout << "Enter the output filename: ";
    std::cin >> output_filename;
    
    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    Graph graph = read_graph_from_file(input_filename);

    auto [T, Pi] = dijkstra(graph, source);

    write_results_to_file(output_filename, T, Pi);

    std::cout << "Results written to " << output_filename << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <graphviz/gvc.h>

struct Edge {
    int source;
    int target;
    double weight;
    int color;
};

std::vector<Edge> edges; // List of edges

void generateDotFile(const std::vector<Edge>& edges, const std::string& dotFileName) {
    std::ofstream dotFile(dotFileName);

    if (!dotFile.is_open()) {
        std::cerr << "Failed to open DOT file for writing." << std::endl;
        return;
    }

    dotFile << "graph G {" << std::endl;

    for (const Edge& edge : edges) {
        dotFile << edge.source << " -- " << edge.target << " [label=\"" << edge.weight << "\", color=\"" << edge.color << "\"];" << std::endl;
    }

    dotFile << "}" << std::endl;
    dotFile.close();
}

void renderDotFile(const std::string& dotFileName, const std::string& outputFileName) {
    std::string command = "dot -Tpng " + dotFileName + " -o " + outputFileName;
    system(command.c_str());
}

int main() {
    // Add your edges with weights and colors to the 'edges' vector
    edges.push_back({0, 1, 2.0, 1});
    edges.push_back({0, 2, 3.0, 2});
    edges.push_back({1, 3, 4.0, 1});
    edges.push_back({1, 4, 5.0, 2});
    // Add more edges as needed

    // Generate a DOT file
    generateDotFile(edges, "graph.dot");

    // Render the DOT file to a PNG image
    renderDotFile("graph.dot", "graph.png");

    std::cout << "Graph visualization saved as 'graph.png'." << std::endl;

    return 0;
}

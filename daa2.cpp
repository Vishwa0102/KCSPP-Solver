#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include<bits/stdc++.h>
using namespace std;
struct Label {
    double distance;
    std::set<int> colors;
    std::vector<int> path;

    // Define a custom comparison operator for Label
    bool operator==(const Label& other) const {
        return distance == other.distance && colors == other.colors && path == other.path;
    }
};

struct Edge {
    int target;
    double weight;
    int color;
};

std::vector<std::vector<Edge>> graph; // Adjacency list representation

Label DP(const int s, const int t, const int k) {
    std::vector<std::vector<Label>> D(graph.size());
    std::vector<Label> L;

    // Initialize the label for the source node
    Label source_label{0.0, {}, {s}};
    L.push_back(source_label);
    D[s].push_back(source_label);

    double best_distance = std::numeric_limits<double>::max();
    Label best_label;

    while (!L.empty()) {
        Label current_label = L.front();
        L.erase(L.begin());

        if (current_label.distance >= best_distance) {
            // Skip labels that can't lead to a better solution
            continue;
        }

        int current_node = current_label.path.back();

        if (current_node == t) {
            if (current_label.colors.size() <= k && current_label.distance < best_distance) {
                best_distance = current_label.distance;
                best_label = current_label;
            }
        }

        for (const Edge& edge : graph[current_node]) {
            int neighbor = edge.target;
            if (std::find(current_label.path.begin(), current_label.path.end(), neighbor) == current_label.path.end()) {
                Label new_label = current_label;
                new_label.distance += edge.weight;
                new_label.colors.insert(edge.color);
                new_label.path.push_back(neighbor);

                bool add_label = true;

                for (Label& existing_label : D[neighbor]) {
                    if (new_label.distance > existing_label.distance &&
                        new_label.colors == existing_label.colors) {
                        add_label = false;
                        break;
                    }

                    if (new_label.distance < existing_label.distance &&
                        new_label.colors == existing_label.colors) {
                        D[neighbor].erase(std::remove(D[neighbor].begin(), D[neighbor].end(), existing_label), D[neighbor].end());
                    }
                }

                if (add_label) {
                    L.push_back(new_label);
                    D[neighbor].push_back(new_label);
                }
            }
        }
    }

    return best_label;
}

int main() {
    // Initialize the graph
int num_nodes = 20;
graph.resize(num_nodes);

// Sample edges with weights and colors
graph[0].push_back({1, 2.0, 1});
graph[0].push_back({2, 3.0, 2});
graph[1].push_back({3, 4.0, 1});
graph[1].push_back({4, 5.0, 2});
graph[2].push_back({5, 6.0, 3});
graph[2].push_back({6, 7.0, 4});
graph[3].push_back({7, 8.0, 5});
graph[3].push_back({8, 9.0, 6});
graph[4].push_back({9, 10.0, 2});
graph[4].push_back({10, 11.0, 3});
graph[5].push_back({11, 12.0, 1});
graph[5].push_back({12, 13.0, 5});
graph[6].push_back({13, 14.0, 4});
graph[6].push_back({14, 15.0, 3});
graph[7].push_back({15, 16.0, 1});
graph[7].push_back({16, 17.0, 2});
graph[8].push_back({17, 18.0, 4});
graph[8].push_back({18, 19.0, 5});
graph[9].push_back({19, 20.0, 6});
graph[9].push_back({10, 21.0, 2});
graph[10].push_back({11, 22.0, 3});
graph[10].push_back({12, 23.0, 1});
graph[11].push_back({12, 24.0, 4});
graph[11].push_back({13, 25.0, 5});
graph[12].push_back({13, 26.0, 1});
graph[12].push_back({14, 27.0, 3});
graph[13].push_back({15, 28.0, 6});
graph[13].push_back({16, 29.0, 2});
graph[14].push_back({17, 30.0, 4});
graph[14].push_back({18, 31.0, 5});
graph[15].push_back({19, 32.0, 1});
graph[15].push_back({20, 33.0, 3});
graph[16].push_back({20, 34.0, 6});

    int source = 0;
    int target = 8;
    int k = 3;

    Label result = DP(source, target, k);

    // Process and print the result
    if (result.path.empty()) {
        std::cout << "No path found." << std::endl;
    } else {
        std::cout << "Shortest path: ";
        for (int node : result.path) {
            std::cout << node << " ";
        }
        std::cout<<"\ncost ="<<result.distance<<endl;
        std::cout << std::endl;
    }

    return 0;
}

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>

class Graph {
public:
    Graph(int vertices);
    void add_edge(int u, int v);
    void find_critical_elements();
    std::vector<int> get_articulation_points() const;
    std::vector<std::pair<int, int>> get_bridges() const;

private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;
    std::vector<int> tin;
    std::vector<int> low;
    int timer;
    std::vector<int> articulation_points;
    std::vector<std::pair<int, int>> bridges;
    
    void dfs(int v, int parent);
};

#endif
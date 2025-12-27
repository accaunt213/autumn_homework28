#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(int vertices);
    void add_edge(int from, int to);
    int min_edges_to_make_strongly_connected();
    
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> adj_rev;
    
    void dfs1(int v, std::vector<bool>& visited, std::vector<int>& order);
    void dfs2(int v, std::vector<bool>& visited, std::vector<int>& component);
};

#endif
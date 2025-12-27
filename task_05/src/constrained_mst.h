#ifndef CONSTRAINED_MST_H
#define CONSTRAINED_MST_H

#include <vector>
#include <limits>

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
};

class ConstrainedMST {
private:
    int n;
    int d;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
    
    int find_set(int v, std::vector<int>& parent);
    void union_sets(int a, int b, std::vector<int>& parent, std::vector<int>& rank);
    bool kruskal_with_degree_limit(std::vector<Edge>& result, int& total_weight);
    int degree_in_tree(int v, const std::vector<bool>& in_tree, const std::vector<Edge>& tree_edges);
    bool can_add_edge(const Edge& edge, const std::vector<bool>& in_tree, 
                      const std::vector<int>& degree, const std::vector<int>& parent);
    
public:
    ConstrainedMST(int vertices, int max_degree);
    void add_edge(int u, int v, int w);
    int find_constrained_mst();
};

#endif
#ifndef LCA_H
#define LCA_H

#include <vector>
#include <cmath>

class LCAFinder {
private:
    int n;
    int log_n;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> up;
    std::vector<int> depth;
    std::vector<int> parent;
    
    void dfs(int v, int p);
    void preprocess();
    
public:
    LCAFinder(int vertices);
    void add_edge(int u, int v);
    void build(int root = 0);
    int find_lca(int u, int v);
    int get_depth(int v);
};

#endif
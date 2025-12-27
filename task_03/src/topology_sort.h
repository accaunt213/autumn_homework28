#ifndef TOPOLOGY_SORT_H
#define TOPOLOGY_SORT_H

#include <vector>

class TopologySorter {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> color; // 0 - белый, 1 - серый, 2 - черный
    std::vector<int> order;
    bool has_cycle;
    
    bool dfs(int v);
    
public:
    TopologySorter(int vertices);
    void add_edge(int from, int to);
    std::vector<int> topological_sort();
    bool hasCycle() const;
};

#endif
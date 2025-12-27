#include "topology_sort.h"
#include <algorithm>

TopologySorter::TopologySorter(int vertices) : n(vertices), has_cycle(false) {
    adj.resize(n);
    color.resize(n, 0);
}

void TopologySorter::add_edge(int from, int to) {
    adj[from].push_back(to);
}

bool TopologySorter::dfs(int v) {
    color[v] = 1;
    
    for (int u : adj[v]) {
        if (color[u] == 0) {
            if (dfs(u)) {
                return true;
            }
        } else if (color[u] == 1) {
            has_cycle = true;
            return true;//нашл цикл
        }
    }
    
    color[v] = 2; //чернный обработан
    order.push_back(v);
    return false;
}

std::vector<int> TopologySorter::topological_sort() {
    order.clear();
    has_cycle = false;
    std::fill(color.begin(), color.end(), 0);
    
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            if (dfs(i)) {
                break;
            }
        }
    }
    
    if (has_cycle) {
        return std::vector<int>();
    }
    
    std::reverse(order.begin(), order.end());
    return order;
}

bool TopologySorter::hasCycle() const {
    return has_cycle;
}
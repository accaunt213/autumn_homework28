#include <iostream>
#include <set>
#include "graph.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    Graph g(n);
    
    std::set<std::pair<int, int>> unique_edges;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        
        if (u == v) continue;
        
        auto edge = std::make_pair(std::min(u, v), std::max(u, v));
        if (unique_edges.find(edge) == unique_edges.end()) {
            g.add_edge(u, v);
            unique_edges.insert(edge);
        }
    }
    
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    std::cout << articulation_points.size() << std::endl;
    
    if (articulation_points.empty()) {
        std::cout << "-" << std::endl;
    } else {
        for (size_t i = 0; i < articulation_points.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << articulation_points[i] + 1;
        }
        std::cout << std::endl;
    }
    
    std::cout << bridges.size() << std::endl;
    
    if (bridges.empty()) {
        std::cout << "-" << std::endl;
    } else {
        for (size_t i = 0; i < bridges.size(); ++i) {
            if (i > 0) std::cout << "; ";
            std::cout << bridges[i].first + 1 << " " << bridges[i].second + 1;
        }
        std::cout << std::endl;
    }
    
    return 0;
}
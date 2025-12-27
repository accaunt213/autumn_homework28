#include <iostream>
#include "topology_sort.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    TopologySorter sorter(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        sorter.add_edge(u - 1, v - 1);
    }
    
    std::vector<int> result = sorter.topological_sort();
    
    if (result.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << result[i] + 1;
        }
        std::cout << std::endl;
    }
    
    return 0;
}
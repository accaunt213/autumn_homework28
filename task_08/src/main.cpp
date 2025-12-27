#include <iostream>
#include "lca.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    LCAFinder lca_finder(n);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        lca_finder.add_edge(u - 1, v - 1);
    }
    
    lca_finder.build(0);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca_finder.find_lca(u - 1, v - 1) + 1 << std::endl;
    }
    
    return 0;
}
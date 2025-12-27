#include <iostream>
#include "graph.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    Graph g(n);
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }
    
    std::cout << g.min_edges_to_make_strongly_connected() << std::endl;
    
    return 0;
}
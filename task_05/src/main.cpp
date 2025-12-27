#include <iostream>
#include "constrained_mst.h"

int main() {
    int n, m, d;
    std::cin >> n >> m >> d;
    
    ConstrainedMST mst_solver(n, d);
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        mst_solver.add_edge(u - 1, v - 1, w);
    }
    
    int result = mst_solver.find_constrained_mst();
    
    if (result == -1) {
        std::cout << "Невозможно построить остовное дерев" << std::endl;
    } else {
        std::cout << result << std::endl;
    }
    
    return 0;
}
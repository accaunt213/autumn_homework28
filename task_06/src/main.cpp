#include <iostream>
#include "max_flow.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    MaxFlowSolver solver(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        solver.add_edge(u - 1, v - 1, c);
    }
    
    int source = 0;
    int sink = n - 1;
    
    int max_flow = solver.max_flow(source, sink);
    
    std::cout << max_flow << std::endl;
    
    return 0;
}
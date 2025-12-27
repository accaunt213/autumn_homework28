#include <iostream>
#include <vector>
#include "johnson.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    JohnsonSolver solver(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        solver.add_edge(u - 1, v - 1, w);
    }
    
    std::vector<std::vector<long long>> result = solver.solve();
    
    if (result.empty()) {
        std::cout << -1 << std::endl;
        return 0;
    }
    
    const long long INF = std::numeric_limits<long long>::max() / 2;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (result[i][j] == INF) {
                std::cout << "INF";
            } else {
                std::cout << result[i][j];
            }
            
            if (j < n - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    return 0;
}
#ifndef JOHNSON_H
#define JOHNSON_H

#include <vector>
#include <limits>

class JohnsonSolver {
private:
    const long long INF = std::numeric_limits<long long>::max() / 2;
    int n;
    std::vector<std::vector<std::pair<int, long long>>> adj;
    
    bool bellman_ford(std::vector<long long>& h);
    std::vector<long long> dijkstra(int start, const std::vector<long long>& h);
    
public:
    JohnsonSolver(int vertices);
    void add_edge(int u, int v, long long w);
    std::vector<std::vector<long long>> solve();
};

#endif
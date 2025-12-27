#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

class MaxFlowSolver {
private:
    struct Edge {
        int to;
        int capacity;
        int flow;
        int rev;
        
        Edge(int to, int capacity, int rev) 
            : to(to), capacity(capacity), flow(0), rev(rev) {}
    };
    
    int n;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> level;
    std::vector<int> ptr;
    
    bool bfs(int source, int sink);
    int dfs(int v, int sink, int flow);
    
public:
    MaxFlowSolver(int vertices);
    void add_edge(int from, int to, int capacity);
    int max_flow(int source, int sink);
};

#endif
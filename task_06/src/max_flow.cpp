#include "max_flow.h"

MaxFlowSolver::MaxFlowSolver(int vertices) : n(vertices) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
}

void MaxFlowSolver::add_edge(int from, int to, int capacity) {
    Edge forward(to, capacity, adj[to].size());
    Edge backward(from, 0, adj[from].size());
    
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}

bool MaxFlowSolver::bfs(int source, int sink) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<int> q;
    
    level[source] = 0;
    q.push(source);
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        for (const Edge& edge : adj[v]) {
            if (level[edge.to] == -1 && edge.flow < edge.capacity) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }
    
    return level[sink] != -1;
}

int MaxFlowSolver::dfs(int v, int sink, int pushed) {
    if (pushed == 0) return 0;
    if (v == sink) return pushed;
    
    for (int& i = ptr[v]; i < (int)adj[v].size(); ++i) {
        Edge& edge = adj[v][i];
        
        if (level[edge.to] == level[v] + 1 && edge.flow < edge.capacity) {
            int min_capacity = std::min(pushed, edge.capacity - edge.flow);
            int tr = dfs(edge.to, sink, min_capacity);
            
            if (tr > 0) {
                edge.flow += tr;
                adj[edge.to][edge.rev].flow -= tr;
                return tr;
            }
        }
    }
    
    return 0;
}

int MaxFlowSolver::max_flow(int source, int sink) {
    int flow = 0;
    
    while (bfs(source, sink)) {
        std::fill(ptr.begin(), ptr.end(), 0);
        
        while (int pushed = dfs(source, sink, std::numeric_limits<int>::max())) {
            flow += pushed;
        }
    }
    
    return flow;
}
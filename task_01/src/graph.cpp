#include "graph.h"
#include <algorithm>

Graph::Graph(int vertices) : n(vertices), timer(0) {
    adj.resize(n);
}

void Graph::add_edge(int u, int v) {
    if (u == v) return;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::dfs(int v, int parent) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    
    for (int to : adj[v]) {
        if (to == parent) continue;
        
        if (visited[to]) {
            low[v] = std::min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = std::min(low[v], low[to]);
            
            if (low[to] >= tin[v] && parent != -1) {
                articulation_points.push_back(v);
            }
            
            if (low[to] > tin[v]) {
                bridges.push_back({std::min(v, to), std::max(v, to)});
            }
            
            children++;
        }
    }
    
    if (parent == -1 && children > 1) {
        articulation_points.push_back(v);
    }
}

void Graph::find_critical_elements() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    articulation_points.clear();
    bridges.clear();
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
    
    std::sort(articulation_points.begin(), articulation_points.end());
    articulation_points.erase(std::unique(articulation_points.begin(), articulation_points.end()), articulation_points.end());
    std::sort(bridges.begin(), bridges.end());
}

std::vector<int> Graph::get_articulation_points() const {
    return articulation_points;
}

std::vector<std::pair<int, int>> Graph::get_bridges() const {
    return bridges;
}
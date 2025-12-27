#include "graph.h"
#include <algorithm>
#include <stack>

Graph::Graph(int vertices) : n(vertices) {
    adj.resize(n);
    adj_rev.resize(n);
}

void Graph::add_edge(int from, int to) {
    adj[from].push_back(to);
    adj_rev[to].push_back(from);
}

void Graph::dfs1(int v, std::vector<bool>& visited, std::vector<int>& order) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u, visited, order);
        }
    }
    order.push_back(v);
}

void Graph::dfs2(int v, std::vector<bool>& visited, std::vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : adj_rev[v]) {
        if (!visited[u]) {
            dfs2(u, visited, component);
        }
    }
}

int Graph::min_edges_to_make_strongly_connected() {
    std::vector<bool> visited(n, false);
    std::vector<int> order;
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i, visited, order);
        }
    }
    
    std::fill(visited.begin(), visited.end(), false);
    std::vector<int> comp_id(n, -1);
    std::vector<std::vector<int>> components;
    
    for (int i = order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (!visited[v]) {
            std::vector<int> component;
            dfs2(v, visited, component);
            for (int u : component) {
                comp_id[u] = components.size();
            }
            components.push_back(component);
        }
    }
    
    int comp_count = components.size();
    if (comp_count == 1) {
        return 0;
    }
    
    std::vector<int> in_degree(comp_count, 0);
    std::vector<int> out_degree(comp_count, 0);
    
    for (int v = 0; v < n; ++v) {
        for (int u : adj[v]) {
            if (comp_id[v] != comp_id[u]) {
                out_degree[comp_id[v]]++;
                in_degree[comp_id[u]]++;
            }
        }
    }
    
    int sources = 0;
    int sinks = 0;
    
    for (int i = 0; i < comp_count; ++i) {
        if (in_degree[i] == 0) sources++;
        if (out_degree[i] == 0) sinks++;
    }
    
    return std::max(sources, sinks);
}
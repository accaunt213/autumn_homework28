#include "johnson.h"
#include <queue>
#include <vector>
#include <algorithm>

JohnsonSolver::JohnsonSolver(int vertices) : n(vertices) {
    adj.resize(n);
}

void JohnsonSolver::add_edge(int u, int v, long long w) {
    adj[u].emplace_back(v, w);
}

bool JohnsonSolver::bellman_ford(std::vector<long long>& h) {
    h.assign(n + 1, INF);
    h[n] = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int u = 0; u <= n; ++u) {
            if (h[u] == INF) continue;
            
            if (u == n) {
                for (int v = 0; v < n; ++v) {
                    if (h[v] > h[u]) {
                        h[v] = h[u];
                    }
                }
            } else {
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    long long w = edge.second;
                    if (h[v] > h[u] + w) {
                        h[v] = h[u] + w;
                    }
                }
            }
        }
    }
    
    for (int u = 0; u <= n; ++u) {
        if (h[u] == INF) continue;
        
        if (u == n) {
            for (int v = 0; v < n; ++v) {
                if (h[v] > h[u]) return false;
            }
        } else {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                long long w = edge.second;
                if (h[v] > h[u] + w) {
                    return false;
                }
            }
        }
    }
    
    h.pop_back();
    return true;
}

std::vector<long long> JohnsonSolver::dijkstra(int start, const std::vector<long long>& h) {
    std::vector<long long> dist(n, INF);
    dist[start] = 0;
    
    std::priority_queue<std::pair<long long, int>, 
                       std::vector<std::pair<long long, int>>,
                       std::greater<std::pair<long long, int>>> pq;
    pq.emplace(0, start);
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d != dist[u]) continue;
        
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second + h[u] - h[v];
            
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    
    for (int v = 0; v < n; ++v) {
        if (dist[v] != INF) {
            dist[v] = dist[v] - h[start] + h[v];
        }
    }
    
    return dist;
}

std::vector<std::vector<long long>> JohnsonSolver::solve() {
    std::vector<long long> h;
    if (!bellman_ford(h)) {
        return {};
    }
    
    std::vector<std::vector<long long>> distances(n);
    for (int i = 0; i < n; ++i) {
        distances[i] = dijkstra(i, h);
    }
    
    return distances;
}
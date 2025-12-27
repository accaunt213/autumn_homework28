#include "constrained_mst.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

ConstrainedMST::ConstrainedMST(int vertices, int max_degree) : n(vertices), d(max_degree) {
    adj.resize(n);
}

void ConstrainedMST::add_edge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    adj[u].push_back(edges.size() - 1);
    adj[v].push_back(edges.size() - 1);
}

int ConstrainedMST::find_set(int v, std::vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void ConstrainedMST::union_sets(int a, int b, std::vector<int>& parent, std::vector<int>& rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int ConstrainedMST::degree_in_tree(int v, const std::vector<bool>& in_tree, const std::vector<Edge>& tree_edges) {
    int degree = 0;
    for (const auto& edge : tree_edges) {
        if (edge.u == v || edge.v == v) {
            degree++;
        }
    }
    return degree;
}

bool ConstrainedMST::can_add_edge(const Edge& edge, const std::vector<bool>& in_tree, 
                                  const std::vector<int>& degree, const std::vector<int>& parent) {
    if (find_set(edge.u, (std::vector<int>&)parent) == find_set(edge.v, (std::vector<int>&)parent))
        return false;
    
    if (in_tree[edge.u] && in_tree[edge.v] && degree[edge.u] >= d)
        return false;
    
    if (in_tree[edge.u] && degree[edge.u] >= d)
        return false;
    
    if (in_tree[edge.v] && degree[edge.v] >= d)
        return false;
    
    return true;
}

bool ConstrainedMST::kruskal_with_degree_limit(std::vector<Edge>& result, int& total_weight) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    
    std::vector<int> parent(n);
    std::vector<int> rank(n, 0);
    std::vector<int> degree(n, 0);
    std::vector<bool> in_tree(n, false);
    
    for (int i = 0; i < n; i++)
        parent[i] = i;
    
    result.clear();
    total_weight = 0;
    int edges_added = 0;
    
    for (const auto& edge : edges) {
        if (edges_added == n - 1)
            break;
        
        if (can_add_edge(edge, in_tree, degree, parent)) {
            int u = edge.u;
            int v = edge.v;
            
            if (find_set(u, parent) != find_set(v, parent)) {
                union_sets(u, v, parent, rank);
                result.push_back(edge);
                total_weight += edge.weight;
                degree[u]++;
                degree[v]++;
                in_tree[u] = true;
                in_tree[v] = true;
                edges_added++;
            }
        }
    }
    
    if (edges_added != n - 1) {
        return false;
    }
    
    for (int i = 0; i < n; i++) {
        if (degree[i] > d) {
            return false;
        }
    }
    
    return true;
}

int ConstrainedMST::find_constrained_mst() {
    std::vector<Edge> mst_edges;
    int total_weight;
    
    if (kruskal_with_degree_limit(mst_edges, total_weight)) {
        return total_weight;
    }
    
    return -1;
}
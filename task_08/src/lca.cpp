#include "lca.h"
#include <algorithm>

LCAFinder::LCAFinder(int vertices) : n(vertices) {
    adj.resize(n);
    log_n = log2(n) + 1;
    up.resize(n, std::vector<int>(log_n + 1));
    depth.resize(n);
    parent.resize(n, -1);
}

void LCAFinder::add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void LCAFinder::dfs(int v, int p) {
    parent[v] = p;
    depth[v] = (p == -1) ? 0 : depth[p] + 1;
    
    up[v][0] = p;
    for (int i = 1; i <= log_n; ++i) {
        if (up[v][i-1] != -1) {
            up[v][i] = up[up[v][i-1]][i-1];
        } else {
            up[v][i] = -1;
        }
    }
    
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
        }
    }
}

void LCAFinder::preprocess() {
    for (int i = 0; i < n; ++i) {
        std::fill(up[i].begin(), up[i].end(), -1);
    }
}

void LCAFinder::build(int root) {
    preprocess();
    dfs(root, -1);
}

int LCAFinder::find_lca(int u, int v) {
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }
    
    int diff = depth[u] - depth[v];
    for (int i = log_n; i >= 0; --i) {
        if (diff & (1 << i)) {
            u = up[u][i];
        }
    }
    
    if (u == v) {
        return u;
    }
    
    for (int i = log_n; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    return parent[u];
}

int LCAFinder::get_depth(int v) {
    return depth[v];
}
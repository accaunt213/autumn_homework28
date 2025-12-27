#include <iostream>
#include <vector>
#include <cassert>
#include "johnson.h"

void test_simple_graph() {
    JohnsonSolver solver(4);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 2, 4);
    solver.add_edge(1, 2, 2);
    solver.add_edge(1, 3, 5);
    solver.add_edge(2, 3, 1);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    assert(result[0][0] == 0);
    assert(result[0][1] == 1);
    assert(result[0][2] == 3);
    assert(result[0][3] == 4);
    
    std::cout << "test_simple_graph: OK" << std::endl;
}

void test_negative_weights() {
    JohnsonSolver solver(3);
    solver.add_edge(0, 1, -1);
    solver.add_edge(0, 2, 4);
    solver.add_edge(1, 2, 3);
    solver.add_edge(1, 0, 2);
    solver.add_edge(2, 0, -2);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    assert(result[0][0] == 0);
    assert(result[0][1] == -1);
    assert(result[0][2] == 2);
    
    std::cout << "test_negative_weights: OK" << std::endl;
}

void test_no_negative_cycle() {
    JohnsonSolver solver(4);
    solver.add_edge(0, 1, 1);
    solver.add_edge(1, 2, -1);
    solver.add_edge(2, 3, -1);
    solver.add_edge(3, 0, -1);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    std::cout << "test_no_negative_cycle: OK" << std::endl;
}

void test_disconnected_graph() {
    JohnsonSolver solver(3);
    solver.add_edge(0, 1, 2);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    const long long INF = std::numeric_limits<long long>::max() / 2;
    assert(result[0][2] == INF);
    assert(result[2][0] == INF);
    assert(result[2][1] == INF);
    
    std::cout << "test_disconnected_graph: OK" << std::endl;
}

void test_single_vertex() {
    JohnsonSolver solver(1);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    assert(result[0][0] == 0);
    
    std::cout << "test_single_vertex: OK" << std::endl;
}

void test_negative_cycle() {
    JohnsonSolver solver(3);
    solver.add_edge(0, 1, 1);
    solver.add_edge(1, 2, 2);
    solver.add_edge(2, 0, -4);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(result.empty());
    
    std::cout << "test_negative_cycle: OK" << std::endl;
}

void test_large_weights() {
    JohnsonSolver solver(3);
    solver.add_edge(0, 1, 1000000000);
    solver.add_edge(1, 2, -1000000000);
    solver.add_edge(0, 2, 500000000);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    assert(result[0][2] == 500000000);
    
    std::cout << "test_large_weights: OK" << std::endl;
}

void test_multiple_edges() {
    JohnsonSolver solver(3);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 1, 3);
    solver.add_edge(1, 2, 2);
    solver.add_edge(0, 2, 4);
    solver.add_edge(0, 2, 5);
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    assert(result[0][1] == 1);
    assert(result[0][2] == 3);
    
    std::cout << "test_multiple_edges: OK" << std::endl;
}

void test_complete_graph() {
    int n = 4;
    JohnsonSolver solver(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                solver.add_edge(i, j, i + j + 1);
            }
        }
    }
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    for (int i = 0; i < n; ++i) {
        assert(result[i][i] == 0);
    }
    
    std::cout << "test_complete_graph: OK" << std::endl;
}

void test_chain_graph() {
    JohnsonSolver solver(5);
    for (int i = 0; i < 4; ++i) {
        solver.add_edge(i, i + 1, 1);
    }
    
    std::vector<std::vector<long long>> result = solver.solve();
    assert(!result.empty());
    
    assert(result[0][4] == 4);
    assert(result[4][0] == std::numeric_limits<long long>::max() / 2);
    
    std::cout << "test_chain_graph: OK" << std::endl;
}

int main() {
    test_simple_graph();
    test_negative_weights();
    test_no_negative_cycle();
    test_disconnected_graph();
    test_single_vertex();
    test_negative_cycle();
    test_large_weights();
    test_multiple_edges();
    test_complete_graph();
    test_chain_graph();
    return 0;
}
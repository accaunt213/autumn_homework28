#include <iostream>
#include <cassert>
#include "max_flow.h"

void test_simple_graph() {
    MaxFlowSolver solver(4);
    solver.add_edge(0, 1, 3);
    solver.add_edge(0, 2, 2);
    solver.add_edge(1, 2, 1);
    solver.add_edge(1, 3, 3);
    solver.add_edge(2, 3, 2);
    
    int flow = solver.max_flow(0, 3);
    assert(flow == 4);
    std::cout << " OK" << std::endl;
}

void test_single_edge() {
    MaxFlowSolver solver(2);
    solver.add_edge(0, 1, 5);
    
    int flow = solver.max_flow(0, 1);
    assert(flow == 5);
    std::cout << "test OK" << std::endl;
}

void test_bottleneck() {
    MaxFlowSolver solver(4);
    solver.add_edge(0, 1, 10);
    solver.add_edge(0, 2, 10);
    solver.add_edge(1, 3, 5);
    solver.add_edge(2, 3, 5);
    
    int flow = solver.max_flow(0, 3);
    assert(flow == 10);
    std::cout << "OK" << std::endl;
}

void test_complex_graph() {
    MaxFlowSolver solver(6);
    solver.add_edge(0, 1, 16);
    solver.add_edge(0, 2, 13);
    solver.add_edge(1, 2, 10);
    solver.add_edge(1, 3, 12);
    solver.add_edge(2, 1, 4);
    solver.add_edge(2, 4, 14);
    solver.add_edge(3, 2, 9);
    solver.add_edge(3, 5, 20);
    solver.add_edge(4, 3, 7);
    solver.add_edge(4, 5, 4);
    
    int flow = solver.max_flow(0, 5);
    assert(flow == 23);
    std::cout << "OK" << std::endl;
}

void test_disconnected() {
    MaxFlowSolver solver(4);
    solver.add_edge(0, 1, 5);
    solver.add_edge(2, 3, 5);
    
    int flow = solver.max_flow(0, 3);
    assert(flow == 0);
    std::cout << "test OK" << std::endl;
}

void test_multiple_paths() {
    MaxFlowSolver solver(5);
    solver.add_edge(0, 1, 10);
    solver.add_edge(0, 2, 5);
    solver.add_edge(1, 2, 15);
    solver.add_edge(1, 3, 10);
    solver.add_edge(2, 3, 10);
    solver.add_edge(3, 4, 15);
    
    int flow = solver.max_flow(0, 4);
    assert(flow == 15);
    std::cout << "test OK" << std::endl;
}

void test_reverse_edges() {
    MaxFlowSolver solver(3);
    solver.add_edge(0, 1, 10);
    solver.add_edge(1, 0, 5);
    solver.add_edge(1, 2, 10);
    
    int flow = solver.max_flow(0, 2);
    assert(flow == 10);
    std::cout << "OK" << std::endl;
}

void test_parallel_edges() {
    MaxFlowSolver solver(3);
    solver.add_edge(0, 1, 5);
    solver.add_edge(0, 1, 10);
    solver.add_edge(1, 2, 15);
    
    int flow = solver.max_flow(0, 2);
    assert(flow == 15);
    std::cout << "OK" << std::endl;
}

void test_zero_capacity() {
    MaxFlowSolver solver(3);
    solver.add_edge(0, 1, 10);
    solver.add_edge(1, 2, 0);
    
    int flow = solver.max_flow(0, 2);
    assert(flow == 0);
    std::cout << "OK" << std::endl;
}

void test_large_flow() {
    MaxFlowSolver solver(100);
    
    for (int i = 0; i < 99; ++i) {
        solver.add_edge(i, i + 1, 1000);
    }
    
    int flow = solver.max_flow(0, 99);
    assert(flow == 1000);
    std::cout << "OK" << std::endl;
}

int main() {
    test_simple_graph();
    test_single_edge();
    test_bottleneck();
    test_complex_graph();
    test_disconnected();
    test_multiple_paths();
    test_reverse_edges();
    test_parallel_edges();
    test_zero_capacity();
    test_large_flow();
    
    std::cout << "test passed" << std::endl;
    return 0;
}
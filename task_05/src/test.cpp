#include <iostream>
#include <cassert>
#include "constrained_mst.h"

void test_simple_graph_with_degree_2() {
    ConstrainedMST solver(4, 2);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 2, 2);
    solver.add_edge(0, 3, 3);
    solver.add_edge(1, 2, 4);
    solver.add_edge(1, 3, 5);
    solver.add_edge(2, 3, 6);
    
    int result = solver.find_constrained_mst();
    assert(result == 6);
    std::cout << "test_simple_graph_with_degree_2: OK" << std::endl;
}

void test_simple_graph_with_degree_1() {
    ConstrainedMST solver(4, 1);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 2, 2);
    solver.add_edge(0, 3, 3);
    solver.add_edge(1, 2, 4);
    solver.add_edge(1, 3, 5);
    solver.add_edge(2, 3, 6);
    
    int result = solver.find_constrained_mst();
    assert(result == -1);
    std::cout << "test_simple_graph_with_degree_1: OK" << std::endl;
}

void test_chain_graph() {
    ConstrainedMST solver(5, 2);
    solver.add_edge(0, 1, 1);
    solver.add_edge(1, 2, 2);
    solver.add_edge(2, 3, 3);
    solver.add_edge(3, 4, 4);
    solver.add_edge(0, 2, 5);
    solver.add_edge(1, 3, 6);
    
    int result = solver.find_constrained_mst();
    assert(result == 10);
    std::cout << "test_chain_graph: OK" << std::endl;
}

void test_star_graph() {
    ConstrainedMST solver(5, 4);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 2, 1);
    solver.add_edge(0, 3, 1);
    solver.add_edge(0, 4, 1);
    solver.add_edge(1, 2, 10);
    solver.add_edge(2, 3, 10);
    solver.add_edge(3, 4, 10);
    solver.add_edge(4, 1, 10);
    
    int result = solver.find_constrained_mst();
    assert(result == 4);
    std::cout << "test_star_graph: OK" << std::endl;
}

void test_star_graph_with_degree_2() {
    ConstrainedMST solver(5, 2);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 2, 1);
    solver.add_edge(0, 3, 1);
    solver.add_edge(0, 4, 1);
    solver.add_edge(1, 2, 2);
    solver.add_edge(2, 3, 3);
    solver.add_edge(3, 4, 4);
    solver.add_edge(4, 1, 5);
    
    int result = solver.find_constrained_mst();
    assert(result == 10);
    std::cout << "test_star_graph_with_degree_2: OK" << std::endl;
}

void test_complete_graph_degree_3() {
    ConstrainedMST solver(6, 3);
    
    for (int i = 0; i < 6; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            solver.add_edge(i, j, i + j + 1);
        }
    }
    
    int result = solver.find_constrained_mst();
    assert(result != -1);
    std::cout << "test_complete_graph_degree_3: OK" << std::endl;
}

void test_single_vertex() {
    ConstrainedMST solver(1, 0);
    int result = solver.find_constrained_mst();
    assert(result == 0);
    std::cout << "test_single_vertex: OK" << std::endl;
}

void test_two_vertices() {
    ConstrainedMST solver(2, 1);
    solver.add_edge(0, 1, 5);
    
    int result = solver.find_constrained_mst();
    assert(result == 5);
    std::cout << "test_two_vertices: OK" << std::endl;
}

void test_two_vertices_degree_0() {
    ConstrainedMST solver(2, 0);
    solver.add_edge(0, 1, 5);
    
    int result = solver.find_constrained_mst();
    assert(result == -1);
    std::cout << "test_two_vertices_degree_0: OK" << std::endl;
}

void test_disconnected_graph() {
    ConstrainedMST solver(4, 2);
    solver.add_edge(0, 1, 1);
    solver.add_edge(2, 3, 1);
    
    int result = solver.find_constrained_mst();
    assert(result == -1);
    std::cout << "test_disconnected_graph: OK" << std::endl;
}

void test_multiple_edges() {
    ConstrainedMST solver(3, 2);
    solver.add_edge(0, 1, 1);
    solver.add_edge(0, 1, 2);
    solver.add_edge(1, 2, 3);
    solver.add_edge(1, 2, 4);
    solver.add_edge(0, 2, 5);
    solver.add_edge(0, 2, 6);
    
    int result = solver.find_constrained_mst();
    assert(result == 4);
    std::cout << "test_multiple_edges: OK" << std::endl;
}

void test_self_loops() {
    ConstrainedMST solver(3, 2);
    solver.add_edge(0, 0, 1);
    solver.add_edge(0, 1, 2);
    solver.add_edge(1, 2, 3);
    solver.add_edge(2, 2, 4);
    
    int result = solver.find_constrained_mst();
    assert(result == 5);
    std::cout << "test_self_loops: OK" << std::endl;
}

int main() {
    test_simple_graph_with_degree_2();
    test_simple_graph_with_degree_1();
    test_chain_graph();
    test_star_graph();
    test_star_graph_with_degree_2();
    test_complete_graph_degree_3();
    test_single_vertex();
    test_two_vertices();
    test_two_vertices_degree_0();
    test_disconnected_graph();
    test_multiple_edges();
    test_self_loops();
    
    return 0;
}
#include <iostream>
#include <cassert>
#include "graph.h"

void test_example1() {
    Graph g(2);
    g.add_edge(0, 1);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 1);
    std::cout << "test_example1: OK" << std::endl;
}

void test_example2() {
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 2);
    std::cout << "test_example2: OK" << std::endl;
}

void test_example3() {
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 2);
    std::cout << "test_example3: OK" << std::endl;
}

void test_already_strongly_connected() {
    Graph g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 0);
    std::cout << "test_already_strongly_connected: OK" << std::endl;
}

void test_disconnected_components() {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 2);
    g.add_edge(4, 5);
    g.add_edge(5, 4);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 3);
    std::cout << "test_disconnected_components: OK" << std::endl;
}

void test_single_vertex() {
    Graph g(1);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 0);
    std::cout << "test_single_vertex: OK" << std::endl;
}

void test_no_edges() {
    Graph g(4);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 4);
    std::cout << "test_no_edges: OK" << std::endl;
}

void test_chain() {
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 1);
    std::cout << "test_chain: OK" << std::endl;
}

void test_diamond() {
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    
    int result = g.min_edges_to_make_strongly_connected();
    assert(result == 1);
    std::cout << "test_diamond: OK" << std::endl;
}

int main() {
    test_example1();
    test_example2();
    test_example3();
    test_already_strongly_connected();
    test_disconnected_components();
    test_single_vertex();
    test_no_edges();
    test_chain();
    test_diamond();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
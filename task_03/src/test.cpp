#include <iostream>
#include <cassert>
#include <vector>
#include "topology_sort.h"

void test_simple_dag() {
    TopologySorter sorter(4);
    sorter.add_edge(0, 1);
    sorter.add_edge(0, 2);
    sorter.add_edge(1, 3);
    sorter.add_edge(2, 3);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 4);
    assert(!sorter.hasCycle());
    
    std::cout << "test_simple_dag: OK" << std::endl;
}

void test_cycle() {
    TopologySorter sorter(3);
    sorter.add_edge(0, 1);
    sorter.add_edge(1, 2);
    sorter.add_edge(2, 0);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.empty());
    assert(sorter.hasCycle());
    
    std::cout << "test_cycle: OK" << std::endl;
}

void test_multiple_components() {
    TopologySorter sorter(6);
    sorter.add_edge(0, 1);
    sorter.add_edge(1, 2);
    sorter.add_edge(3, 4);
    sorter.add_edge(4, 5);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 6);
    assert(!sorter.hasCycle());
    
    std::cout << "test_multiple_components: OK" << std::endl;
}

void test_self_loop() {
    TopologySorter sorter(2);
    sorter.add_edge(0, 0);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.empty());
    assert(sorter.hasCycle());
    
    std::cout << "test_self_loop: OK" << std::endl;
}

void test_empty_graph() {
    TopologySorter sorter(5);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 5);
    assert(!sorter.hasCycle());
    
    std::cout << "test_empty_graph: OK" << std::endl;
}

void test_large_dag() {
    TopologySorter sorter(1000);
    for (int i = 0; i < 999; ++i) {
        sorter.add_edge(i, i + 1);
    }
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 1000);
    assert(!sorter.hasCycle());
    
    std::cout << "test_large_dag: OK" << std::endl;
}

void test_diamond_shape() {
    TopologySorter sorter(4);
    sorter.add_edge(0, 1);
    sorter.add_edge(0, 2);
    sorter.add_edge(1, 3);
    sorter.add_edge(2, 3);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 4);
    assert(!sorter.hasCycle());
    
    bool valid = true;
    std::vector<int> pos(4);
    for (size_t i = 0; i < result.size(); ++i) {
        pos[result[i]] = i;
    }
    
    if (pos[0] >= pos[1] || pos[0] >= pos[2] || pos[1] >= pos[3] || pos[2] >= pos[3]) {
        valid = false;
    }
    
    assert(valid);
    std::cout << "test_diamond_shape: OK" << std::endl;
}

void test_complex_dag() {
    TopologySorter sorter(7);
    sorter.add_edge(0, 1);
    sorter.add_edge(0, 2);
    sorter.add_edge(1, 3);
    sorter.add_edge(1, 4);
    sorter.add_edge(2, 5);
    sorter.add_edge(3, 6);
    sorter.add_edge(4, 6);
    sorter.add_edge(5, 6);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.size() == 7);
    assert(!sorter.hasCycle());
    
    std::cout << "test_complex_dag: OK" << std::endl;
}

void test_complex_cycle() {
    TopologySorter sorter(5);
    sorter.add_edge(0, 1);
    sorter.add_edge(1, 2);
    sorter.add_edge(2, 3);
    sorter.add_edge(3, 4);
    sorter.add_edge(4, 1);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.empty());
    assert(sorter.hasCycle());
    
    std::cout << "test_complex_cycle: OK" << std::endl;
}

void test_mixed_edges() {
    TopologySorter sorter(8);
    sorter.add_edge(0, 1);
    sorter.add_edge(0, 2);
    sorter.add_edge(1, 3);
    sorter.add_edge(2, 3);
    sorter.add_edge(4, 5);
    sorter.add_edge(5, 6);
    sorter.add_edge(6, 7);
    sorter.add_edge(7, 5);
    
    std::vector<int> result = sorter.topological_sort();
    assert(result.empty());
    assert(sorter.hasCycle());
    
    std::cout << "test_mixed_edges: OK" << std::endl;
}

int main() {
    test_simple_dag();
    test_cycle();
    test_multiple_components();
    test_self_loop();
    test_empty_graph();
    test_large_dag();
    test_diamond_shape();
    test_complex_dag();
    test_complex_cycle();
    test_mixed_edges();
    
    return 0;
}
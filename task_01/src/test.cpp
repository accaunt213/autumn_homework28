#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "graph.h"

void test_single_edge() {
    Graph g(2);
    g.add_edge(0, 1);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.empty());
    assert(bridges.size() == 1);
    assert(bridges[0] == std::make_pair(0, 1));
    
    std::cout << "test_single_edge: OK" << std::endl;
}

void test_triangle() {
    Graph g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.empty());
    assert(bridges.empty());
    
    std::cout << "test_triangle: OK" << std::endl;
}

void test_chain_4_vertices() {
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.size() == 2);
    assert(std::find(articulation_points.begin(), articulation_points.end(), 1) != articulation_points.end());
    assert(std::find(articulation_points.begin(), articulation_points.end(), 2) != articulation_points.end());
    assert(bridges.size() == 3);
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 1)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(1, 2)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(2, 3)) != bridges.end());
    
    std::cout << "test_chain_4_vertices: OK" << std::endl;
}

void test_star_graph() {
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.size() == 1);
    assert(articulation_points[0] == 0);
    assert(bridges.size() == 4);
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 1)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 2)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 3)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 4)) != bridges.end());
    
    std::cout << "test_star_graph: OK" << std::endl;
}

void test_disconnected_graph() {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 3);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.empty());
    assert(bridges.empty());
    
    std::cout << "test_disconnected_graph: OK" << std::endl;
}

void test_complex_graph() {
    Graph g(7);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 3);
    g.add_edge(4, 6);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    std::vector<int> expected_articulation = {1, 3, 4};
    std::vector<std::pair<int, int>> expected_bridges = {{1, 3}, {4, 6}};
    
    assert(articulation_points.size() == expected_articulation.size());
    for (int point : expected_articulation) {
        assert(std::find(articulation_points.begin(), articulation_points.end(), point) != articulation_points.end());
    }
    
    assert(bridges.size() == expected_bridges.size());
    for (auto& bridge : expected_bridges) {
        assert(std::find(bridges.begin(), bridges.end(), bridge) != bridges.end());
    }
    
    std::cout << "test_complex_graph: OK" << std::endl;
}

void test_two_triangles_connected() {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 3);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.size() == 2);
    assert(std::find(articulation_points.begin(), articulation_points.end(), 2) != articulation_points.end());
    assert(std::find(articulation_points.begin(), articulation_points.end(), 3) != articulation_points.end());
    assert(bridges.size() == 1);
    assert(bridges[0] == std::make_pair(2, 3));
    
    std::cout << "test_two_triangles_connected: OK" << std::endl;
}

void test_parallel_edges() {
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 1);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.size() == 1);
    assert(articulation_points[0] == 1);
    assert(bridges.size() == 1);
    assert(bridges[0] == std::make_pair(1, 2));
    
    std::cout << "test_parallel_edges: OK" << std::endl;
}

void test_self_loops() {
    Graph g(3);
    g.add_edge(0, 0);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 2);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.size() == 1);
    assert(articulation_points[0] == 1);
    assert(bridges.size() == 2);
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(0, 1)) != bridges.end());
    assert(std::find(bridges.begin(), bridges.end(), std::make_pair(1, 2)) != bridges.end());
    
    std::cout << "test_self_loops: OK" << std::endl;
}

void test_empty_graph() {
    Graph g(5);
    g.find_critical_elements();
    
    std::vector<int> articulation_points = g.get_articulation_points();
    std::vector<std::pair<int, int>> bridges = g.get_bridges();
    
    assert(articulation_points.empty());
    assert(bridges.empty());
    
    std::cout << "test_empty_graph: OK" << std::endl;
}

int main() {
    test_single_edge();
    test_triangle();
    test_chain_4_vertices();
    test_star_graph();
    test_disconnected_graph();
    test_complex_graph();
    test_two_triangles_connected();
    test_parallel_edges();
    test_self_loops();
    test_empty_graph();
    
    return 0;
}
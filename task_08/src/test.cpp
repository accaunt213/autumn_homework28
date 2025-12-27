#include <iostream>
#include <vector>
#include <cassert>
#include "lca.h"

void test_simple_tree() {
    LCAFinder finder(6);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    finder.add_edge(2, 5);
    
    finder.build(0);
    
    assert(finder.find_lca(3, 4) == 1);
    assert(finder.find_lca(3, 5) == 0);
    assert(finder.find_lca(4, 5) == 0);
    assert(finder.find_lca(1, 3) == 1);
    assert(finder.find_lca(0, 5) == 0);
    
}

void test_chain_tree() {
    LCAFinder finder(5);
    finder.add_edge(0, 1);
    finder.add_edge(1, 2);
    finder.add_edge(2, 3);
    finder.add_edge(3, 4);
    
    finder.build(0);
    
    assert(finder.find_lca(0, 4) == 0);
    assert(finder.find_lca(2, 4) == 2);
    assert(finder.find_lca(3, 4) == 3);
    assert(finder.find_lca(1, 3) == 1);
}

void test_binary_tree() {
    LCAFinder finder(7);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    finder.add_edge(2, 5);
    finder.add_edge(2, 6);
    
    finder.build(0);
    
    assert(finder.find_lca(3, 4) == 1);
    assert(finder.find_lca(3, 5) == 0);
    assert(finder.find_lca(5, 6) == 2);
    assert(finder.find_lca(4, 6) == 0);
    assert(finder.find_lca(3, 1) == 1);
    
}

void test_star_tree() {
    LCAFinder finder(6);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(0, 3);
    finder.add_edge(0, 4);
    finder.add_edge(0, 5);
    
    finder.build(0);
    
    assert(finder.find_lca(1, 2) == 0);
    assert(finder.find_lca(3, 4) == 0);
    assert(finder.find_lca(2, 5) == 0);
    assert(finder.find_lca(1, 1) == 1);
    
}

void test_complex_tree() {
    LCAFinder finder(12);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    finder.add_edge(2, 5);
    finder.add_edge(2, 6);
    finder.add_edge(3, 7);
    finder.add_edge(3, 8);
    finder.add_edge(5, 9);
    finder.add_edge(5, 10);
    finder.add_edge(9, 11);
    
    finder.build(0);
    
    assert(finder.find_lca(7, 8) == 3);
    assert(finder.find_lca(7, 4) == 1);
    assert(finder.find_lca(9, 10) == 5);
    assert(finder.find_lca(11, 6) == 2);
    assert(finder.find_lca(8, 11) == 0);
    assert(finder.find_lca(7, 3) == 3);
    
}

void test_depth() {
    LCAFinder finder(5);
    finder.add_edge(0, 1);
    finder.add_edge(1, 2);
    finder.add_edge(2, 3);
    finder.add_edge(3, 4);
    
    finder.build(0);
    
    assert(finder.get_depth(0) == 0);
    assert(finder.get_depth(1) == 1);
    assert(finder.get_depth(2) == 2);
    assert(finder.get_depth(3) == 3);
    assert(finder.get_depth(4) == 4);
    
}

void test_same_vertex() {
    LCAFinder finder(5);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    
    finder.build(0);
    
    assert(finder.find_lca(2, 2) == 2);
    assert(finder.find_lca(3, 3) == 3);
    assert(finder.find_lca(0, 0) == 0);
    
}

void test_parent_child() {
    LCAFinder finder(4);
    finder.add_edge(0, 1);
    finder.add_edge(1, 2);
    finder.add_edge(2, 3);
    
    finder.build(0);
    
    assert(finder.find_lca(1, 2) == 1);
    assert(finder.find_lca(2, 3) == 2);
    assert(finder.find_lca(1, 3) == 1);
    
}

void test_different_root() {
    LCAFinder finder(7);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    finder.add_edge(2, 5);
    finder.add_edge(2, 6);
    
    finder.build(2);
    
    assert(finder.find_lca(5, 6) == 2);
    assert(finder.find_lca(3, 5) == 2);
    assert(finder.find_lca(0, 6) == 2);
    
}

void test_random_queries() {
    LCAFinder finder(8);
    finder.add_edge(0, 1);
    finder.add_edge(0, 2);
    finder.add_edge(1, 3);
    finder.add_edge(1, 4);
    finder.add_edge(2, 5);
    finder.add_edge(3, 6);
    finder.add_edge(3, 7);
    
    finder.build(0);
    
    std::vector<std::pair<int, int>> queries = {
        {6, 7}, {4, 5}, {6, 4}, {7, 5}, {1, 7}, {0, 6}
    };
    
    std::vector<int> expected = {3, 0, 1, 0, 1, 0};
    
    for (size_t i = 0; i < queries.size(); ++i) {
        int u = queries[i].first;
        int v = queries[i].second;
        int result = finder.find_lca(u, v);
        assert(result == expected[i]);
    }
    
}

int main() {
    test_simple_tree();
    test_chain_tree();
    test_binary_tree();
    test_star_tree();
    test_complex_tree();
    test_depth();
    test_same_vertex();
    test_parent_child();
    test_different_root();
    test_random_queries();
    
    std::cout << "test pass" << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>
#include "segment_tree.h"

void test_simple_queries() {
    std::vector<int> arr = {5, 3, 7, 3, 2};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(1, 4) == 2); // индексы с 0: [1..4] -> [3,7,3,2] min=2
    seg_tree.update_value(2, 1); // arr[2] = 1
    assert(seg_tree.range_min(0, 2) == 1); // [5,3,1] min=1
    assert(seg_tree.range_min(2, 2) == 1); // [1] min=1
    seg_tree.update_value(4, 10); // arr[4] = 10
    assert(seg_tree.range_min(3, 4) == 3); // [3,10] min=3
    
    std::cout << "test  OK" << std::endl;
}

void test_single_element() {
    std::vector<int> arr = {5};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 0) == 5);
    seg_tree.update_value(0, 10);
    assert(seg_tree.range_min(0, 0) == 10);
    
    std::cout << "test  OK" << std::endl;
}

void test_all_same() {
    std::vector<int> arr(10, 5);
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 9) == 5);
    assert(seg_tree.range_min(3, 7) == 5);
    seg_tree.update_value(5, 2);
    assert(seg_tree.range_min(0, 9) == 2);
    assert(seg_tree.range_min(0, 4) == 5);
    
    std::cout << "test OK" << std::endl;
}

void test_ascending() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 9) == 1);
    assert(seg_tree.range_min(3, 6) == 4);
    seg_tree.update_value(0, 100);
    assert(seg_tree.range_min(0, 9) == 2);
    assert(seg_tree.range_min(0, 0) == 100);
    
    std::cout << "OK" << std::endl;
}

void test_descending() {
    std::vector<int> arr = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 9) == 1);
    assert(seg_tree.range_min(0, 4) == 6);
    seg_tree.update_value(9, 100);
    assert(seg_tree.range_min(0, 9) == 2);
    assert(seg_tree.range_min(8, 9) == 2);
    
    std::cout << "OK" << std::endl;
}

void test_random_updates() {
    std::vector<int> arr = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 9) == 0);
    assert(seg_tree.range_min(0, 4) == 1);
    assert(seg_tree.range_min(5, 9) == 0);
    
    seg_tree.update_value(9, 10);
    assert(seg_tree.range_min(0, 9) == 1);
    
    seg_tree.update_value(3, 5);
    assert(seg_tree.range_min(0, 4) == 2);
    
    seg_tree.update_value(1, 0);
    assert(seg_tree.range_min(0, 9) == 0);
    assert(seg_tree.range_min(0, 0) == 5);
    
    std::cout << "OK" << std::endl;
}

void test_full_range_queries() {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    SegmentTree seg_tree(arr);
    
    for (int i = 0; i < 10; ++i) {
        for (int j = i; j < 10; ++j) {
            int expected = *std::min_element(arr.begin() + i, arr.begin() + j + 1);
            assert(seg_tree.range_min(i, j) == expected);
        }
    }
    
    std::cout << "OK" << std::endl;
}

void test_edge_cases() {
    std::vector<int> arr = {INT_MAX, INT_MIN, 0, -100, 100};
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, 4) == INT_MIN);
    assert(seg_tree.range_min(2, 4) == -100);
    seg_tree.update_value(1, 1000);
    assert(seg_tree.range_min(0, 4) == -100);
    assert(seg_tree.range_min(0, 1) == INT_MAX);
    
    std::cout << " OK" << std::endl;
}

void test_large_array() {
    const int N = 1000;
    std::vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = i % 100;
    }
    
    SegmentTree seg_tree(arr);
    
    assert(seg_tree.range_min(0, N-1) == 0);
    assert(seg_tree.range_min(100, 199) == 0);
    seg_tree.update_value(500, -5);
    assert(seg_tree.range_min(0, N-1) == -5);
    assert(seg_tree.range_min(0, 499) == 0);
    
    std::cout << "test  OK" << std::endl;
}

void test_sequential_updates() {
    std::vector<int> arr = {10, 10, 10, 10, 10};
    SegmentTree seg_tree(arr);
    
    for (int i = 0; i < 5; ++i) {
        seg_tree.update_value(i, i);
        assert(seg_tree.range_min(0, 4) == 0);
    }
    
    for (int i = 0; i < 5; ++i) {
        assert(seg_tree.range_min(i, i) == i);
    }
    
    std::cout << "test OK" << std::endl;
}

int main() {
    test_simple_queries();
    test_single_element();
    test_all_same();
    test_ascending();
    test_descending();
    test_random_updates();
    test_full_range_queries();
    test_edge_cases();
    test_large_array();
    test_sequential_updates();
    
    std::cout << "test pass" << std::endl;
    return 0;
}
#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>
#include <algorithm>
#include <climits>

class SegmentTree {
private:
    int n;
    std::vector<int> tree;
    std::vector<int> arr;
    
    void build(int node, int left, int right);
    void update(int node, int left, int right, int index, int value);
    int query(int node, int left, int right, int ql, int qr);
    
public:
    SegmentTree(const std::vector<int>& nums);
    void update_value(int index, int value);
    int range_min(int left, int right);
};

#endif
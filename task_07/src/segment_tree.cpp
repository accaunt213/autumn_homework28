#include "segment_tree.h"

SegmentTree::SegmentTree(const std::vector<int>& nums) {
    n = nums.size();
    arr = nums;
    tree.resize(4 * n);
    build(1, 0, n - 1);
}

void SegmentTree::build(int node, int left, int right) {
    if (left == right) {
        tree[node] = arr[left];
        return;
    }
    
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    tree[node] = std::min(tree[node * 2], tree[node * 2 + 1]);
}

void SegmentTree::update(int node, int left, int right, int index, int value) {
    if (left == right) {
        tree[node] = value;
        arr[left] = value;
        return;
    }
    
    int mid = (left + right) / 2;
    if (index <= mid) {
        update(node * 2, left, mid, index, value);
    } else {
        update(node * 2 + 1, mid + 1, right, index, value);
    }
    
    tree[node] = std::min(tree[node * 2], tree[node * 2 + 1]);
}

int SegmentTree::query(int node, int left, int right, int ql, int qr) {
    if (ql > right || qr < left) {
        return INT_MAX;
    }
    
    if (ql <= left && right <= qr) {
        return tree[node];
    }
    
    int mid = (left + right) / 2;
    int left_min = query(node * 2, left, mid, ql, qr);
    int right_min = query(node * 2 + 1, mid + 1, right, ql, qr);
    return std::min(left_min, right_min);
}

void SegmentTree::update_value(int index, int value) {
    update(1, 0, n - 1, index, value);
}

int SegmentTree::range_min(int left, int right) {
    return query(1, 0, n - 1, left, right);
}
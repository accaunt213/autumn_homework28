#include <iostream>
#include <vector>
#include "segment_tree.h"

int main() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    
    SegmentTree seg_tree(arr);
    
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        
        if (type == 1) {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg_tree.range_min(l - 1, r - 1) << std::endl;
        } else if (type == 2) {
            int idx, val;
            std::cin >> idx >> val;
            seg_tree.update_value(idx - 1, val);
        }
    }
    
    return 0;
}
#pragma once
#include <vector>
#include <memory>


struct OctreeNode {
    std::vector<std::unique_ptr<OctreeNode>> children;
};

#pragma once
#include <array>
#include <vector>
#include <memory>
#include <stdint.h>
#include <cmath>
#include "sandbox/math/vec3.h"
#include "sandbox/math/vec4.h"
#include "sandbox/octree/utility/morton_BMI.h"

namespace sandbox {

struct OctreeNode 
{
    std::array<std::unique_ptr<OctreeNode>, 8> children;
    uint16_t material;
};


// Octree with explicit depth
class Octree 
{
public:
    Octree(uint8_t depth = 10) : m_treeDepth(depth), m_treeHalfWidth(pow(2, depth - 1)) {
        m_root = std::make_unique<OctreeNode>();
    }
    void insert(vec3 position, uint16_t material) {
        u_vec3 uv3 = convertToUnsigned(position);
        uint64_t morton = libmorton::m3D_e_BMI<uint64_t, int>(uv3.x, uv3.y, uv3.z);

        OctreeNode* trackingBranch = m_root.get();
        for (int i = m_treeDepth; i > 0; i--) {
            uint32_t octLocation = (morton >> (3 * i)) & 0b111;
            if (trackingBranch->children[octLocation] == nullptr) {
                std::cout << "null\n";
                trackingBranch->children[octLocation].reset(new OctreeNode()); // Create new branch if it doesn't exist
            }
            trackingBranch = trackingBranch->children[octLocation].get(); // Update the tracking branch to point to the next level branch as specified by index
        }

        // Set the color of the leaf node and increment the node count
        trackingBranch->material = material;
    }

private:
    std::unique_ptr<OctreeNode> m_root; // Root node of the tree
    uint8_t m_treeDepth;                // Max depth of the tree
    uint32_t m_treeHalfWidth;           // Half the width of the total tree

    u_vec3 convertToUnsigned(vec3& position) { // Converts a signed vec3 to an unsigned u_vec3 since octrees don't work with negatives
        return u_vec3(
            position.x + m_treeHalfWidth,
            position.y + m_treeHalfWidth,
            position.z + m_treeHalfWidth
        );
    } 
};


}




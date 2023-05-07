#pragma once
#include <array>
#include <memory>
#include <stdint.h>
#include <cmath>
#include "sandbox/math/vec3.h"
#include "sandbox/utility/morton_BMI.h"
#include "sandbox/memory/mem_arena.h"

namespace sandbox {

// We need a custom deleter for the unique pointers here because the Octree class uses a memory arena.
// If the unique pointers free memory in the arena, that could lead to segfault issues
// Maybe switch to raw pointers instead
struct NoDelete {
    template <typename T>
    void operator()(T*) const noexcept {}
};

// ======================
// REQUIREMENTS:
// ======================
//
// Build args for faster performance: (most of these are optional)
//    -mbmi2 (compiler intrinsics on bmi2 supported CPU's)
//    -03 or -02 (compiler optimizations)
//    -fno-tree-dce (disables dead code elimination)
//
struct OctreeNode 
{
    std::array<std::unique_ptr<OctreeNode, NoDelete>, 8> children; // This approach uses an extensive amount of memory.
    uint16_t material; // low memory usage for material instead of using 3 floats for a color. We could also use a color lookup table
};

// Octree with explicit depth
class Octree 
{
public:
    Octree(ArenaAllocator& allocator, uint8_t depth = 10) 
        : m_treeDepth(depth), 
          m_root(new (allocator.alloc(sizeof(OctreeNode))) OctreeNode()),
          m_allocator(allocator) {
    }

    // Inserts a node into the octree. Insertion benchmarks: ~7ns per insertion. ~143 million insertions/s
    // Traverses up until max_depth for LOD compatibility
    void insert(vec3 position, uint16_t material, uint8_t max_depth) {
        // Makes sure that were not traversing further than the max depth
        assert(max_depth <= m_treeDepth);
        // Convert signed vec3 to an unsigned u_vec3. We do this because the morton encoding doesn't support
        // signed values as input and managing only unsigned values in the octree is easier and efficient
        u_vec3 uv3 = convertToUnsigned(position);
        // Calculate 64 bit morton code using unsigned vec3. ~3ns per calculation
        // A 64 bit morton code can handle an octree depth of at most 21. This means an x, y, z range of 2,097,152 units. 
        // If each leaf node unit is 4 inches in game, that equates to ~132 miles
        uint64_t morton = libmorton::m3D_e_BMI<uint64_t, int>(uv3.x, uv3.y, uv3.z); 
        // Keep track of the current branch we are in
        OctreeNode* trackingBranch = m_root.get();
        for (int i = 0; i < max_depth; i++) {
            // Extract the furthest (least significant) bits from the morton code. These bits represent the higher level nodes in the tree. The most significant bits represent the leaf nodes
            uint64_t octLocation = (morton >> (3 * (m_treeDepth - i))) & 0b111;
            if (trackingBranch->children[octLocation] == nullptr) { // Create new branch if it doesn't exist
                // This heap allocation takes the most time here: ~0.003 ms which equates to 200ms for 200k insertions. 
                // What we want to do is pass in a custom arena allocator into the octree class so we can get faster and controlled allocations.
                // this line: new (mem) OctreeNode(), constructs a new octree node at the memory address we allocated here:
                void* mem = m_allocator.alloc(sizeof(OctreeNode)); // Allocate new memory block of size 'OctreeNode' and return the pointer to that block
                if (mem == nullptr) {
                    throw AllocatorOutOfMemoryError(m_allocator);
                }
                // Construct new node at child location using the memory address we allocated in the arena
                trackingBranch->children[octLocation].reset(new (mem) OctreeNode()); 
            }
            // Update the tracking branch to point to the next level branch as specified by octLocation
            trackingBranch = trackingBranch->children[octLocation].get(); 
        }

        // Set the color of the leaf node and increment the node count
        trackingBranch->material = material;
    }

    // Returns a pointer to a leaf node (at max_depth) it exists. Returns nullptr otherwise.
    // Traverses up until max_depth for LOD compatibility
    OctreeNode* find(vec3 position, uint8_t max_depth) {
        // Makes sure that were not traversing further than the max depth
        assert(max_depth <= m_treeDepth); 

        u_vec3 uv3 = convertToUnsigned(position);
        uint64_t morton = libmorton::m3D_e_BMI<uint64_t, int>(uv3.x, uv3.y, uv3.z);

        OctreeNode* trackingBranch = m_root.get();
        for (int i = 0; i < max_depth; i++) {
            uint64_t octLocation = (morton >> (3 * (m_treeDepth - i))) & 0b111;
            if (trackingBranch->children[octLocation] == nullptr) { 
                return nullptr;
            }
            trackingBranch = trackingBranch->children[octLocation].get(); 
        }
        return trackingBranch;
    }

    // Converts a signed vec3 to an unsigned u_vec3 since octrees don't work with negatives
    u_vec3 convertToUnsigned(vec3& position) { 
        return u_vec3(
            position.x + m_treeHalfWidth,
            position.y + m_treeHalfWidth,
            position.z + m_treeHalfWidth
        );
    } 

private:
    ArenaAllocator& m_allocator;
    std::unique_ptr<OctreeNode, NoDelete> m_root;   // Root node of the tree
    uint8_t m_treeDepth;                            // Max depth of the tree. Depth starts at m_treeDepth and goes down to 0. A depth of 0 is the leaf nodes
    uint32_t m_treeHalfWidth;                       // Half the width of the total tree. We need this for converting signed vec3's to unsigned vec3's
};


}




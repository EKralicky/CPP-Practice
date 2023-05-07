#include <iostream>
#include <bitset>
#include "octree/octree.h"
#include "profiling/profiling.h"
#include "utility/morton_BMI.h"
#include "memory/mem_arena.h"


int main()
{

    // data for arena allocator
    std::cout << "OctreeNode size: " << sizeof(sandbox::OctreeNode) << "\n";
    size_t arena_size = 1000000 * sizeof(sandbox::OctreeNode);
    std::byte* arena_buffer = new std::byte[arena_size];

    const uint8_t tree_depth = 10;
    ArenaAllocator allocator(arena_buffer, arena_size);
    sandbox::Octree octree(allocator, tree_depth);

    RUN_SCOPED_PROFILER(std::chrono::nanoseconds)
    int size = 64;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                try {
                    octree.insert(vec3(i, j, k), 15, tree_depth);
                } catch (const AllocatorOutOfMemoryError& e) {
                    std::cerr << e.what() << "\n";
                    return 1;
                }
            }
        }
    }

    auto found_node = octree.find(vec3(33, 13, 56), tree_depth);
    if (found_node) {
        //std::cout << found_node->material << "\n";
    } else {
        std::cout << "Node not found.\n";
    }

    
    allocator.free_all();
    delete[] arena_buffer;
    return 0;
}

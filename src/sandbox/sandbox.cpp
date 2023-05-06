#include <iostream>
#include <bitset>
#include "octree/standard/octree.h"
#include "profiling/profiling.h"
#include "octree/utility/morton_BMI.h"
#include "octree/memory/mem_arena.h"


int main()
{

    // data for arena allocator
    std::cout << "OctreeNode size: " << sizeof(sandbox::OctreeNode) << "\n";
    size_t arena_size = 1000000 * sizeof(sandbox::OctreeNode);
    std::byte* arena_buffer = new std::byte[arena_size];

    ArenaAllocator allocator(arena_buffer, arena_size);
    sandbox::Octree octree(allocator, 10);

    RUN_SCOPED_PROFILER(std::chrono::nanoseconds)
    uint64_t libsum = 0;
    int size = 64;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                octree.insert(vec3(i, j, k), 15);
                //libsum += libmorton::m3D_e_BMI<uint64_t, int>(i, j, k);
            }
        }
    }
    allocator.free_all();
    delete[] arena_buffer;
    return libsum;
}

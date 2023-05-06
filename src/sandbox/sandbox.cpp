#include <iostream>
#include <bitset>
#include "octree/standard/octree.h"
#include "profiling/profiling.h"
#include "octree/utility/morton_BMI.h"


int main()
{
    RUN_SCOPED_PROFILER(std::chrono::milliseconds)


    sandbox::Octree octree(10);

    

    int size = 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                octree.insert(vec3(i, j, k), 15);
                //libmorton::m3D_e_BMI<uint64_t, int>(i, j, k);
            }
        }
    }


    return 0;
}

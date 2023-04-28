#include <kernel/memory/memory.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cstdio>
#include "memory.h"
#include <sys/mman.h>
#include <errno.h>
#include <stddef.h>
#include <memory>
#include <string.h>

#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))
#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)

uint64_t binaryAddr = 0;
uint64_t stackAddr = 0;
uint8_t* base;

uint8_t* bitmap; // A bitmap of allocated pages

void Memory::Initialize()
{
    std::srand(time(nullptr));

    // ASLR algorithm, according to SwitchBrew wiki
    uint64_t baseAddr = 0x80000000;
    uint64_t randMax = 0x6400;
    uint64_t mapRegionSize = 0x40000000;
    uint64_t heapRegionSize = 0x40000000;

    uint64_t rnd0 = (std::rand() % randMax) << 21;
    uint64_t rnd1 = (std::rand() % randMax) << 21;

    binaryAddr = baseAddr + std::min(rnd0, rnd1);

    // 2MiB align binaryAddr
    binaryAddr = ALIGN(binaryAddr, 0x200000);

    uint64_t heapRegion = binaryAddr + mapRegionSize + std::max(rnd0, rnd1) - std::min(rnd0, rnd1);

    // Just put the stack at the end of the heap (with some randomness, of course)
    stackAddr = heapRegion + heapRegionSize + std::max(rnd0, rnd1) - std::min(rnd0, rnd1);

    if (stackAddr <= heapRegion+heapRegionSize)
    {
        printf("Oops, stack and heap overlap!\n");
        exit(1);
    }

    // mmap 39 bits of memory
    base = (uint8_t*)mmap64(nullptr, 1ULL<<39, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE | MAP_NORESERVE, -1, 0);

    if (base == MAP_FAILED)
    {
        printf("ERROR: Couldn't map 39-bit address space! %s: %d\n", strerror(errno), errno);
        exit(1);
    }

    binaryAddr += (uint64_t)base;
    heapRegion += (uint64_t)base;
    stackAddr += (uint64_t)base;
    stackAddr += 512*1024; // Default stack size is 512KiB

    printf("[INFO]: Main binary will be at 0x%08lx\n", binaryAddr);
    printf("[INFO]: Heap will be at 0x%08lx\n", heapRegion);
    printf("[INFO]: Stack will be at 0x%08lx\n", stackAddr);
}

uint64_t Memory::GetBinaryMapping()
{
    return binaryAddr;
}
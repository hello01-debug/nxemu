#pragma once

#include <cstdint>
#include <kernel/memory/memory.h>

class CPU
{
private:
    uint64_t regs[31];
    uint64_t pc;
    uint64_t sp;
public:
    CPU(uint64_t entry, uint64_t stacktop);

    void Step();
};
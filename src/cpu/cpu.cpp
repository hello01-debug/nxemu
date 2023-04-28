#include "cpu.h"

#include <cstring>

CPU::CPU(uint64_t entry, uint64_t stacktop)
{
    pc = entry;
    sp = stacktop;
    memset(regs, 0, sizeof(regs));
}
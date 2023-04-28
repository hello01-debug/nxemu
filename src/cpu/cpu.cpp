#include "cpu.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

CPU::CPU(uint64_t entry, uint64_t stacktop)
{
    pc = entry;
    sp = stacktop;
    memset(regs, 0, sizeof(regs));
}

void CPU::Step()
{
    uint32_t opcode = Memory::Read32(pc++);

    printf("Unhandled opcode 0x%08x\n", opcode);
    exit(1);
}

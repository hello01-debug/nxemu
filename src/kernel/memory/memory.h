#pragma once

#include <cstdint>

namespace Memory
{

extern uint8_t* base;

void Initialize();

uint64_t GetBinaryMapping();
uint64_t GetInitProcStack();

uint32_t Read32(uint64_t addr);

}
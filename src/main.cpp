#include <loader/nro.h>
#include <kernel/memory/memory.h>
#include <cpu/cpu.h>

int main()
{
    Memory::Initialize();

    NRO* nro = new NRO("sdl-hello.nro");

    CPU* cpu = new CPU(Memory::GetBinaryMapping()-(uint64_t)Memory::base, Memory::GetInitProcStack()-(uint64_t)Memory::base);

    while (1)
        cpu->Step();

    return 0;
}
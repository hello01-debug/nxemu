#include <loader/nro.h>
#include <kernel/memory/memory.h>

int main()
{
    Memory::Initialize();

    NRO* nro = new NRO("sdl-hello.nro");

    return 0;
}
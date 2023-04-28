#include "nro.h"
#include <kernel/memory/memory.h>

NRO::NRO(std::string fileName)
{
    std::ifstream file(fileName, std::ios::ate | std::ios::binary);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    file.read((char*)&hdr, sizeof(Header));

    if (hdr.magic[0] != 'N'
        || hdr.magic[1] != 'R'
        || hdr.magic[2] != 'O'
        || hdr.magic[3] != '0')
    {
        printf("ERROR: Invalid NRO file, magic: %c%c%c%c\n", hdr.magic[0], hdr.magic[1], hdr.magic[2], hdr.magic[3]);
        exit(1);
    }

    if (size > hdr.size)
    {
        printf("[INFO]: NRO contains asset section\n");
    }

    printf("[INFO]: .text starts at base+0x%08x\n", hdr.text.memoryOffset);
    printf("[INFO]: .rodata starts at base+0x%08x\n", hdr.ro.memoryOffset);
    printf("[INFO]: .data starts at base+0x%08x\n", hdr.data.memoryOffset);

    uint64_t base = Memory::GetBinaryMapping();

    for (uint32_t i = 0; i < hdr.text.size; i++)
    {
        uint8_t data = 0;
        file.read((char*)&data, 1);
        *(uint8_t*)(base+hdr.text.memoryOffset+i) = data;
    }

    for (uint32_t i = 0; i < hdr.ro.size; i++)
    {
        uint8_t data = 0;
        file.read((char*)&data, 1);
        *(uint8_t*)(base+hdr.ro.memoryOffset+i) = data;
    }

    for (uint32_t i = 0; i < hdr.data.size; i++)
    {
        uint8_t data = 0;
        file.read((char*)&data, 1);
        *(uint8_t*)(base+hdr.data.memoryOffset+i) = data;
    }
}
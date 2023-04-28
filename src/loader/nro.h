#pragma once

#include <cstdint>
#include <string>
#include <fstream>

class NRO
{
public:
    struct SegmentHeader
    {
        uint32_t memoryOffset;
        uint32_t size;
    };

    struct Header
    {
        uint32_t unused;
        uint32_t mod0;
        uint64_t padding;
        char magic[4];
        uint32_t version;
        uint32_t size;
        uint32_t flags;
        SegmentHeader text;
        SegmentHeader ro;
        SegmentHeader data;
        uint32_t bssSize;
        uint32_t reserved;
        char moduleId[0x20];
        uint32_t DsoHandleOffset;
        uint32_t reserved1;
        SegmentHeader apiInfo;
        SegmentHeader dynStr;
        SegmentHeader dynSym;
    };
private:
    Header hdr;
public:
    NRO(std::string fileName);
};
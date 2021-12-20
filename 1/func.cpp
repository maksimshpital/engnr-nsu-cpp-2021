#include "other.h"

uint32_t adler32(ifstream &file)
{
    uint32_t s1 = 1;
    uint32_t s2 = 0;
    unsigned char ch = 0;
    while (file.read((char*)(ch), sizeof(unsigned char)))
    {
        s1 = (s1 + ch) % 65521;
        s2 = (s2 + s1) % 65521;
    }

    return (s2 << 16) | s1;
}

uint64_t sum64(istream &file)
{
    uint64_t s = 0, res = 0;
    unsigned char ch, end = 0;
    while (file.read((char*)(ch), sizeof(unsigned char)))
    {
        if (end == 8)
        {
            s += res;
            res = 0;
            end = 0;
        }
        res = res << 8;
        res += ch;
        end++;
    }
    s += res;
    return s;
}

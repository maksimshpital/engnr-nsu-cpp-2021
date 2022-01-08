#include "Hash.h"


uint64_t sum64(std::ifstream &inf){
    if (inf.peek() == EOF)
        return 0;
    uint64_t nb = 0, outcome = 0;
    unsigned char symb = 0, last = 0;
    while (inf.read((char*)(&symb), sizeof(unsigned char))){
        if (last == (char)8){
            nb += outcome;
            outcome = 0;
            last = 0;
        }
        outcome = outcome << 8;
        outcome += symb;
        last++;
    }
    nb += outcome;
    return nb;
}

uint32_t adler32(std::ifstream &inf){
    if (inf.peek() == EOF)
        return 1;
    uint32_t nb_1 = 1;
    uint32_t nb_2 = 0;
    unsigned char symb = 0;
    while (inf.read((char*)(&symb), sizeof(unsigned char))){
        nb_1 = (nb_1 + symb) % 65521;
        nb_2 = (nb_2 + nb_1) % 65521;
    }

    return (nb_2 << 16) | nb_1;
}

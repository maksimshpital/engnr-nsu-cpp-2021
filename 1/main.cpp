#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstring>


void help(char* program_name) {
    std::cerr << "Usage:" << std::endl;
    std::cerr << "\t-" << program_name << " <filename> -m <mode>" << std::endl;
    std::cerr << "\t-" << program_name << " -m <mode> <filename>" << std::endl;
    std::cerr << "Options:\n"
              << "\t-h,--help\tShow this help message\n"
              << "\t-m <mode> \tSpecify the hash calculation mode (adler32 or sum64 only)\n"
              << "\t<filename> \tSpecify the file for hash calculation\n"
              << std::endl;
}

uint32_t adler32(std::string& filename) {
    std::ifstream in_file;
    uint8_t x;
    uint32_t s1 = 1;
    uint32_t s2 = 0;

    in_file.open(filename, std::ios::out | std::ios::binary);
    if(!in_file.is_open()) {
        throw std::invalid_argument("File not found");
    }
    while(true){
        x = in_file.get();
        if (!in_file)
            break;
        s1 = (s1 + x) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) + s1;
}

uint64_t charTo64bitNum(const char a[]) {
    uint64_t n = 0;
    int pos = 0;
    for (int i = 7; i >= 0; i--) {
        if(a[i] != 0) {
            n += ((uint64_t)a[i] << pos*8) & ((int64_t)0xFF << pos*8);
            pos++;
        }
    }
    return n;
}

uint64_t sum64(std::string& filename) {
    uint64_t res = 0;
    std::ifstream in_file(filename, std::ios::out | std::ios::binary);
    if(!in_file.is_open()) {
        throw std::invalid_argument("File not found");
    }
    char a[8] = {0};
    while(true){
        memset(a, 0, sizeof(a));
        if (!in_file)
            break;
        in_file.read(a, 8);
        res += charTo64bitNum(a);
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::string mode, filename;
    if((argc != 2) && (argc != 4)) {
        std::cerr << "incorrect argument number" << std::endl;
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if((arg == "-h") || (arg == "--help")) {
            help(argv[0]);
            return 0;
        }else if((arg == "-m") && (i + 1 < argc)) {
            if(i == 1) {
                mode = argv[2];
                filename = argv[3];
            }else if(i == 2) {
                mode = argv[3];
                filename = argv[1];
            }else {
                help(argv[0]);
                return 1;
            }
            if((mode != "adler32") && (mode != "sum64")) {
                std::cerr << "mode must be adler32 or sum64 only" << std::endl;
                return 1;
            }
        }
    }

    try{
        if(mode == "adler32") {
            uint32_t hash32 = adler32(filename);
            std::cout << "Adler32: " << std::hex << hash32 << std::endl;
        }else{
            uint64_t hash64 = sum64(filename);
            std::cout << "Sum64: " << std::hex << hash64 << std::endl;
        }
    }catch (std::exception& err) {
        std::cerr << "Error while processed file: " << err.what();
    }
    return 0;
}
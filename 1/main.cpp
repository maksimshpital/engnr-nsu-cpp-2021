#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

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

int64_t charTo64bitNum(char a[]) {
    int64_t n = 0;
    n = (((int64_t)a[0] << 56) & 0xFF00000000000000U)
        | (((int64_t)a[1] << 48) & 0x00FF000000000000U)
        | (((int64_t)a[2] << 40) & 0x0000FF0000000000U)
        | (((int64_t)a[3] << 32) & 0x000000FF00000000U)
        | ((a[4] << 24) & 0x00000000FF000000U)
        | ((a[5] << 16) & 0x0000000000FF0000U)
        | ((a[6] <<  8) & 0x000000000000FF00U)
        | (a[7]        & 0x00000000000000FFU);
    return n;
}

uint64_t sum64(std::string& filename) {
    std::ifstream in_file;
    uint64_t x;
    uint64_t res = 0;
    in_file.open(filename, std::ios::out | std::ios::binary);
    if(!in_file.is_open()) {
        throw std::invalid_argument("File not found");
    }
    char a[8] = {0};
    while(true){
        in_file.read(a, 8);
        if (!in_file)
            break;
        x = charTo64bitNum(a);
        res += x;
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
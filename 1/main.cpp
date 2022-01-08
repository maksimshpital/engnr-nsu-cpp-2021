#include "Hash.h"


int main(int args, char *argv[])
{
    std::ifstream inf;
    std::string help, folder, method;
    
    help = "Use cases:\n";
    help += "./hasher -m <method> <filename>\n";
    help += "or\n";
    help += "./hasher <filename> -m <method>\n";
    help += "<method> is adler32 or sum64";

    if (args == 2){
        if (!strcmp(argv[1], "-h")){
            std::cout << help << "\n";
            return 0;
        }
        else{
            std::cerr << "Error, invalid command. " << "\n"
                 << help << "\n";
            return 1;
        }
    }
    else if (args == 4){
        if (!(strcmp(argv[1], "-m")) && (!(strcmp(argv[2], "adler32")) || !(strcmp(argv[2], "sum64")))){
            method = argv[2];
            folder = argv[3];
        }
        else if (!(strcmp(argv[2], "-m")) && (!(strcmp(argv[3], "adler32")) || !(strcmp(argv[3], "sum64")))){
            method = argv[3];
            folder = argv[1];
        }
        else{
            std::cerr << "Error, incorrect arguments" << "\n"
                 << help << "\n";
            return 1;
        }
    }
    else{
        if (args == 1){
            std::cerr << "Error, no arguments" << "\n"
                 << help << "\n";
            return 1;
        }
        else{
            std::cerr << "Error, unknown command" << "\n"
                 << help << "\n";
            return 1;
        }
    }

    inf.open(folder, std::ios_base::binary);

    if (!(inf.is_open())){
        std::cerr << "Error, file is not found" << "\n"
             << help << "\n";
        return 1;
    }

    try{
        if (method == "sum64")
            std::cout << std::hex << sum64(inf) << "\n";
        if (method == "adler32")
            std::cout << std::hex << adler32(inf) << "\n";
    }
    catch (std::exception &error){
        std::cerr << error.what();
        return 1;
    }
    return 0;
}
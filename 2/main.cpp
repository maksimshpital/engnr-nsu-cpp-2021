#include <iostream>
#include <fstream>
#include <string>
#include "CommandCreator.h"
#include "Context.h"
#include "AppException.h"


int main(int argc, char** argv) {
    Context ctx;
    CommandCreator creator;
    std::string command;
    if(argc == 1) {
        while (true) {
            // std::cout << "command> ";
            if (std::getline(std::cin, command) {
                // if(command == "exit") {
                //     break;
                // }
                try {
                    creator.proceed(command, ctx);
                } catch (AppException &exception) {
                    std::cerr << exception.what() << std::endl;
                    return -1;
                }
            }
            if (std::cin.peek() == EOF) 
                break;
        }
    } else {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            return -1;
        }
        while (true){
            if (std::getline(file, command)) {
                try {
                    creator.proceed(command, ctx);
                } catch (AppException &exception) {
                    std::cerr << exception.what() << std::endl;
                    return -1;
                }
            }
            if (file.peek() == EOF) 
                break;
        }
    }


    return 0;
}

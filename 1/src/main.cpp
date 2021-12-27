#include<cstring>
#include<fstream>
#include<iostream>

#include"hasher/hasher.h"


void printPrompt() {
	std::cout << "This is simple CLI hashsum counter" << std::endl;
	std::cout << "Usage:" << std::endl << "\thasher -m <mode> filename" << std::endl;
	std::cout << "\thasher filename -m <mode>" << std::endl << "\tWhere <mode> is crc32 or sum32" << std::endl;
}


void suggestHelp() {
	std::cerr << "Invalid command line arguments. Use -h to get help" << std::endl;
}


int callHasher(char* filename, char* mode) {

	std::ifstream in(filename, std::ios::binary);

	if (!in) {
		std::cerr << "Can't open given file: " << filename << std::endl;
		return 1;
	}

	hasher::uint result;

	try {

		if (!std::strncmp(mode, "crc32", 6)) {
			result = hasher::hashCRC32(in);
		} else if (!std::strncmp(mode, "sum32", 6)) {
			result = hasher::hashSum(in);
		} else {
			suggestHelp();
			return 1;
		}

		// Since usually it's common to print hashsum in
		// hexadecimal format, I decided to use std::hex.
		std::cout << std::hex << result << std::endl;

	} catch (const std::exception& exc) {
		std::cerr << "Something went wrong during hashsum counting:"
			<< std::endl << exc.what() << std::endl;
		return 1;
	}

	return 0;
}


int main(int argc, char** argv) {

	if (argc == 2 && !std::strncmp(argv[1], "-h", 3)) {
		printPrompt();
		return 0;
	} else if (argc != 4) {
		suggestHelp();
		return 1;
	}

	if (!std::strncmp(argv[1], "-m", 3)) {
		return callHasher(argv[3], argv[2]);
	} else if (!std::strncmp(argv[2], "-m", 3)) {
		return callHasher(argv[1], argv[3]);
	}

	suggestHelp();
	return 1;
}

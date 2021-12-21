#pragma once

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

std::uint32_t adler32(std::ifstream &file);
std::uint64_t sum64(std::ifstream &file);
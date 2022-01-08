#pragma once

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>


uint64_t sum64 (std::ifstream &file);
uint32_t adler32(std::ifstream &file);

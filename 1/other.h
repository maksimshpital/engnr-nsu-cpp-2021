#pragma once

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

uint32_t adler32(ifstream &file);
uint64_t sum64(ifstream &file);
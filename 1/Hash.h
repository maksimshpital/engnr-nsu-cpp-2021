#pragma once

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdint.h>


uint64_t sum64(ifstream &file);
uint32_t adler32(ifstream &file);

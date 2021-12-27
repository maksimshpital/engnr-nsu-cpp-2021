#pragma once

#include<iostream>


namespace hasher {

	using uint = std::uint32_t;
	using uchar = std::uint8_t;

	size_t formBlocks(uint* buffer, size_t bytesCount);
	
	uint hashSum(std::istream& in);
	uint hashCRC32(std::istream& in);
}

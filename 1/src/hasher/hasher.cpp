#include "hasher.h"

namespace {
	size_t readBytes(std::istream& in, char* buffer, size_t bufferSize) {
		in.read(buffer, bufferSize);
		return in.gcount();
	}
}


namespace hasher {

	constexpr size_t BUFFER_SIZE = 4096;


	size_t formBlocks(uint* buffer, size_t bytesCount) {
		uchar* bytes = reinterpret_cast<uchar*>(buffer);

		size_t tailSize = bytesCount % 4;
		size_t pos = 0;

		for (size_t i = 0; i < (bytesCount - tailSize); i += 4, ++pos) {
			// There could be problems if we simply cast bytes to uint*.
			// My approach to solving problem with endiannes is building
			// uint values with bit operations, since little-endian and
			// big-endian proccessors have the same behaviour in this situation.
			buffer[pos] = (bytes[i] << 24) | (bytes[i + 1] << 16) | (bytes[i + 2] << 8) | bytes[i + 3];
		}


		if (tailSize) {
			uint tail = 0;

			for (size_t i = 0; i < tailSize; i++) {
				tail = (tail << 8) | bytes[bytesCount - tailSize + i];
			}

			tail <<= (8 * (4 - tailSize));

			buffer[pos] = tail;
			pos++;
		}

		return pos;

	}


	uint hashSum(std::istream& in) {
		uint hashsum = 0;
		uint buffer[BUFFER_SIZE/4];

		while (in) {
			size_t bytesCount = readBytes(in, reinterpret_cast<char*>(buffer), BUFFER_SIZE);
			size_t blocksBount = formBlocks(buffer, bytesCount);

			for (size_t i = 0; i < blocksBount/2; ++i) {
				hashsum += ((buffer[i] << 32 | buffer[i+1]);
			}

			if(blocksCount % 2)
				hashsum += (buffer[blocksCount - 1] << 32);
	    }

		return hashsum;
}


	uint hashCRC32(std::istream& in) {
		uchar buffer[BUFFER_SIZE];
		uint crcTable[256];
		uint crc;

		for (int i = 0; i < 256; i++) {
			crc = i;
			for (int j = 0; j < 8; j++) {
				crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320UL : (crc >> 1);
			}
			crcTable[i] = crc;
		}

		crc = 0xFFFFFFFFUL;

		while (in) {
			size_t count = readBytes(in, reinterpret_cast<char*>(buffer), BUFFER_SIZE);

			for (size_t i = 0;i < count; ++i) {
				crc = crcTable[(crc ^ buffer[i]) & 0xFF] ^ (crc >> 8);
			}
		}

		return crc ^ 0xFFFFFFFFUL;
	}
}

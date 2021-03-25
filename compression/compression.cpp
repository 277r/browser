#include <libdeflate.h>
#include "compression.hpp"


/**
 * @brief removes gzip compression
 * @param data the compressed input data
 * @param size optional, the size of the input
 * @param rSize output size return
 * @warning this function has not been tested yet
*/


char* compression::ungzip(char* data, int size, int &rSize){
	// this might leak ram, but we use free now to deallocate this; WARNING: i don't know how this alloc function works but it seems to work like a simple malloc and so seems to work fine with free
	libdeflate_decompressor *hm = libdeflate_alloc_decompressor();

	// output buffer
	size_t osize = 0;
	char *obuffer = new char[size * 10];
	libdeflate_gzip_decompress(hm, data, size, obuffer, size * 2, &osize);
	// set values and return
	rSize = osize;

	// deallocate pointer
	free(hm);
	// debug output
	//std::cout << obuffer << std::endl;
	return obuffer;
}

#include <libdeflate.h>
#include "compression.h"


/**
 * @brief removes gzip compression
 * @param data the compressed input data
 * @param size optional, the size of the input
 * @param rSize output size return
 * @warning this function has not been tested yet
*/
char* ungzip(char* data, int size, int &rSize){
	// output buffer
	size_t osize = 0;
	char *obuffer = new char[size * 2];
	libdeflate_gzip_decompress(0, data, size, obuffer, size * 2, &osize);
	// set values and return
	rSize = osize;
	return obuffer;
}



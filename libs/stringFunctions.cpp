#include "stringFunctions.h"


// check if *data starts with *test
bool startsWith(char* data, char* test){
	// go on until *test == 0
	while (*test != 0 && *data != 0){

		if (*data != *test){
			return 0;
		}
		test++;
		data++;
	}
	return true;
}

bool startsWith(const char *data, char *test)
{
	// go on until *test == 0
	while (*test != 0 && *data != 0)
	{

		if (*data != *test)
		{
			return 0;
		}
		test++;
		data++;
	}
	return true;
}
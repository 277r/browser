#include <fstream>
#include <iostream>
#include <vector>

#include "../libs/stringFunctions.hpp"
// disable gcc string warnings because it works and it's just "it's not allowed by iso standard" i do not care. this is the easiest way without having to rewrite all my functions and it works just as intended

std::vector<std::string> table;

// return true if exists
long long int lookup(char *data){
	
	
	
	return 0;
}

char* preinterpret(char *data){
	// current variable name
	std::string cvarname;
	// go on until end of string
	while (*data != 0){

		// using nested if statements should optimize because we only check for the first letter
	
	
		// check if 'var' and then 
		if (startsWith(data, "v")){
			if (startsWith(data + 1, "a"))
			{
				if (startsWith(data + 2, "r")){
					data += 4;
					// lookup and/or replace
					while (*data != ';' && *data != ',' && *data != ' '){
						// keep adding characters
						cvarname += *data;
						data++;
					}
					//if (lookup())
				}
			}
		}



	
		data++;
	}
	return nullptr;
}


#include <fstream>
#include <iostream>
#include <vector>

#include "../libs/stringFunctions.hpp"

std::vector<std::string> table;

// return true if exists
long long int lookup(std::string name){
	// check if exists, if exists return location, else return other thing
	for (int i = 0; i < table.size(); i++){
		
	}

	return 0;
}

char* preinterpret(char *data){
	// current location, this will be array index
	long long i = 0;
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
					while (*data != ';' && *data != ',' && *data != ' ' && *data != '\n'){
						// keep adding characters
						cvarname += *data;
						data++;
					}
					// we should use whole bytes, that will make it easier to translate, which in turn will result in less time
					// {illegal JS character}{n bytes} 3 bytes seems good enough for me, we can make this 4 bytes later if we want it 
					// _2é~

					if (lookup(cvarname) != 0){
						// exists already, outputdata += data cvarname

					}
					else {
						// doesn't exist, create one, increment i
					}
				}
			}
		}



	
		data++;
	}
	return nullptr;
}


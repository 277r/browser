#include <iostream>


class var {
public:
	char type;
	void *loc;
	
	// on creation
	var(){
		type = 0;
	}
	// on deletion
	~var(){

	}

	// request a pointer
	void set(){

	}

};




/*
int main(){
	// start with 1000 variables, can add more if needed by the script
	var x[1000];
	long long int index = 0;
	// if "var b " is read, change it into "_0", and index++;
	// if the next line says "var f ", turn it into "_1" and index++;
	// keep continueing this for every variable
	// when we're done doing this for variables, functions, and those things. we can start the actual interpreter
}
*/
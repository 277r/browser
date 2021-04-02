#include "interpreter.hpp"


var::var(){
		type = 0;

	}
	var::~var(){
		if (type != 0){
			delete[] loc;
		}
	}

	void var::setType(char mode){
		if (type != 0){
			// delete heap memory
			delete[] loc;
		}
		type = mode;
		switch (mode){
			case 0: {
				// javascript numbers are always stored as doubles, according to w3schools
				loc = new double[1];
			}
			case 2:
			{
				loc = new std::string[1];
			}
		}
	}
#include <iostream>
#include "./network/requests.h"
int main()
{
	std::string h;
	std::cin >> h;
	// make a pointer to the request
	char *x = request::getraw(h, 80);
	std::cout << x;
	// ALWAYS delete getraws after all uses because we used the new operator and don't want memory leaking
	delete[] x;
	
}
 
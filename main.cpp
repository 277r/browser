#include <iostream>
#include "./network/requests.cpp"
int main()
{
	std::string h;
	std::cin >> h;
	request::getraw(h, 80, "0");
}

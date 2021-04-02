#include <iostream>
#include "./network/requests.hpp"
#include "./render/render.hpp"
#include "./tabs/tabs.hpp"
#include <thread>
// make menu
// make a page on startup
// when clicking the + button (new tab), create a new page
// each tab has it's own controlling thread, each of those threads has it's own other threads (rendering, javascript, etc.)
// i want to add a feature so you can detach tabs from one windows to another, or from one window to make it create a new windows

int main()
{
	// commandline arguments handling here (take over browser tab, etc.)

	// create tab, enable all rendering stuff
	std::thread renderThread = std::thread(Render::init);
	// mainTab is the first tab the browser opens
	Tab mainTab;

	while (true)
	{

		std::string h;
		std::cin >> h;
		unsigned int u = 0;

		// call initSSL when starting up
		request::initSSL();
		request::urlDecoder(h, u);
		std::cout << request::getByUrl(h, u) << std::endl;
		/*
	// make a pointer to the request
	char *x = request::getraw(h, 80);

	std::cout << x;
	// ALWAYS delete getraws after all uses because we used the new operator and don't want memory leaking
	delete[] x;
	*/
	}
}
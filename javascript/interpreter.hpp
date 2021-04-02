#include <string>

class var {
	public:
		char type;
		void *loc;
		var();
		~var();
		void setType(char mode);
};
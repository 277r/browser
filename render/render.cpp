#include "render.hpp"
#define PI 3.1415926f


namespace Render {

	// the x and y are just floats, but 0.5 of our screen in x might be different in y, so we have the factor
	// this factor should only be used in functions and user defined functions, do not just use this to multily a value when you need it for something, the function is supposed to do that
	float SCREENFACTOR = 0.5625;
	void drawPolygonh(float cx, float cy, float b, int segments)
	{
		cx *= SCREENFACTOR;
		// pi = 180 degrees
		// (180 degrees * (segments -2)) * segments gives us the amount of degrees we need (radians in this case so 180 degrees == pi radians)
		float anglePerSegment = PI - (PI * float(segments - 2)) / (float)segments;
		glBegin(GL_POLYGON);

		float y = 0;
		float x = 0;
		for (int i = 0; i < segments; i++)
		{
			// amount of degrees needed this time
			float n = anglePerSegment * i;

			// calculate x and y based on length of b, and on the sinus rule
			// the x drop
			x += b * sin(n);
			y += b * sin(0.5 * PI - n);
			glVertex2f(cx + x * SCREENFACTOR, cy + y);
		}
		glEnd();
	}
	void init(){
		GLFWwindow *window;
		// initialize glfw
		if (!glfwInit())
		{
			return;
		}

		// create window
		window = glfwCreateWindow(800, 600, "h browser", NULL, NULL);
		// error if no window
		if (!window)
		{
			glfwTerminate();
			return;
		}
		// do stuff with window
		glfwMakeContextCurrent(window);
		// initialize glew
		/*
	if (!glewInit())
	{
		return -1;
	}*/

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// set interval so we don't make too much useless frames
		glfwSwapInterval(1);

		/*
	// generate buffers
	unsigned int buffer;
	glGenBuffers(1, &buffer);
*/
		while (!glfwWindowShouldClose(window))
		{

			glClear(GL_COLOR_BUFFER_BIT);

			// render here (before glfwswapBuffers)
			
			glfwSwapBuffers(window);

			glfwPollEvents();
		}
		glfwTerminate();
	}

};

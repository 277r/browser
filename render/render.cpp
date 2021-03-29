#include "render.hpp"
#define PI 3.1415926f
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

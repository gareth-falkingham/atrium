#include "atrium.hpp"

// ----------------------------------------------------------------------
// Entry-Point
// ----------------------------------------------------------------------

int main()
{
	Atrium* app;
	app = new Atrium();
	app->run();
	delete app;
	app = 0;
	return EXIT_SUCCESS;
}
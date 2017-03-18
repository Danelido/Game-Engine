#include "Display.h"
#include "Application.h"

int main()
{
	Display::init();	// Initialize the display class
	Application app;	// Variable for our application class
	app.runGameLoop();	// Start our gameloop
	
	return 0;
}
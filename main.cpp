/**
 * @brief Zpg project
 *
 * @details  My Zpg project
 *
 * @author Aleš Laník
 *
 * @year 2025
 **/
#include "Application.h"

int main()
{
	Application app;
	app.check();
	app.createShaders();
	app.createBuffers();
	app.buildScene();
	app.run();
	return 0;
}
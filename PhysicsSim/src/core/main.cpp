/**
* @file main.cpp
* @brief
* Main entry point for the application.
*/

#include "Application.hpp"

//Uncomment to enable memory leak detection
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

/**
* @brief
* Main entry point for the application.
* 
* @return
* 0 if successful, 1 if failed.
* 
* @details
* Create an instance of the application and run it. Sets the starting width and 
* height to 1280x720 and the name of the window to "Physics Sim". The demo flag 
* is set to false by default to run in normal mode. Set to true to run the ImGui 
* demo.
*/
int main()
{
	int width = 1280;
	int height = 720;
	std::string name = "Physics Sim";
	bool demo = false;

	std::unique_ptr<App::Application> app = std::make_unique<App::Application>();
	if(app->Init(name, width, height)) app->Run(demo);

	return 0;
}
#include "Application.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int, char**)
{
	int width = 1280;
	int height = 720;
	string name = "Physics Sim";
	bool demo = false;

	unique_ptr<App::Application> app = make_unique<App::Application>(width, height, name);
	app->Run(demo);

	return 0;
}
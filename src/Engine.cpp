#include "Engine.h"

Engine* Engine::engineInstance = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{

}

Engine* Engine::Instance()
{
	if (engineInstance == nullptr)
	{
		engineInstance = new Engine();
		return engineInstance;
	}

	return engineInstance;
}

void Engine::UpdateEngine()
{
	WindowInfo::Instance()->InitializeWindow(1200, 900, "Bullet Hell Application", NULL, NULL);

	/* While we don't want to close the GLFW window, process the input of our window, add our own background color
	for the window, clear the color buffer bit to render our color to the window, swap the window's buffers,
	process any events waiting for us to do something to it */
	while (!glfwWindowShouldClose(glfwGetCurrentContext()))
	{
		WindowInfo::Instance()->UpdateWindow();
	}

	// Clean the engine after we're done
	WindowInfo::Instance()->~Window();
}

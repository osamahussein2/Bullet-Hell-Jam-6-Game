#include "Engine.h"
#include "ResourceManager.h"
#include "Assets.h"

//#include <Windows.h>

Engine* Engine::engineInstance = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
	ResourceManager::Clear();
	Window::DeleteWindowInstance();
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

void Engine::DeleteEngineInstance()
{
	if (engineInstance){
		delete engineInstance;
		engineInstance = nullptr;
	}
	else {
		std::cerr<<"engineInstance is not valid to delete\n";
	}
}

void Engine::UpdateEngine()
{
	//FreeConsole(); // Don't make the console pop up before the glfw window pops up
	WindowInfo::Instance()->UpdateWindow();
	// The engine is cleaned in it's destructor, which is called by "delete instance" in DeleteEngineInstance() 
}

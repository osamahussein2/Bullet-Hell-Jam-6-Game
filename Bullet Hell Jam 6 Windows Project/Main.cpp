#include "Engine.h"

// Only for builds for subsystems set to console

#ifndef SUBSYSTEM_CONSOLE
#define SUBSYSTEM_CONSOLE

int main()
{
	Engine::Instance()->UpdateEngine();

	return 0;
}

#endif

// Only for builds for subsystems set to Windows

#ifndef SUBSYSTEM_WINDOWS
#define SUBSYSTEM_WINDOWS

int WinMain()
{
	Engine::Instance()->UpdateEngine();

	return 0;
}

#endif
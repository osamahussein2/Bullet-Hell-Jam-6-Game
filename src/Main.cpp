#include "Engine.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Audio.h"

// Only for builds for subsystems set to console

#ifndef SUBSYSTEM_CONSOLE
#define SUBSYSTEM_CONSOLE

int main()
{
	if (!Audio::Instance()->Initialize()) {
		std::cerr << "Failed to initialize audio\n";
		return 1;
	}

	Engine::Instance()->UpdateEngine();

	return 0;
}

#endif

// Only for builds for subsystems set to Windows

#ifndef SUBSYSTEM_WINDOWS
#define SUBSYSTEM_WINDOWS

int WinMain()
{
	if (!Audio::Instance()->Initialize()) {
		std::cerr << "Failed to initialize audio\n";
		return 1;
	}
	

	Engine::Instance()->UpdateEngine();

	return 0;
}

#endif
#include "Engine.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Audio.h"

int main()
{
	if (!Audio::Instance()->Initialize()) {
		std::cerr << "Failed to initialize audio\n";
		return 1;
	}

	Engine::Instance()->UpdateEngine();
	Engine::DeleteEngineInstance();
	Audio::Instance()->Clear();

	return 0;
}
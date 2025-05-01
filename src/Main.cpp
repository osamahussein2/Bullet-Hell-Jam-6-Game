#include "Engine.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Audio.h"

void UpdateDrawFrame();

int main()
{
	if (!Audio::Instance()->Initialize()) {
		std::cerr << "Failed to initialize audio\n";
		return 1;
	}

	{
		float scale = 1.0;
		if (!WindowInfo::Instance()->InitializeWindow(
				WindowInfo::Instance()->GetGameSize().x * scale,
				WindowInfo::Instance()->GetGameSize().y * scale,
			 	"Bullet Hell Application", NULL, NULL
			)){
			std::cerr << "Failed to initialize window\n";
			return 1;
		}
	}
	

	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
	#else

	/* While we don't want to close the GLFW window, process the input of our window, add our own background color
	for the window, clear the color buffer bit to render our color to the window, swap the window's buffers,
	process any events waiting for us to do something to it */
	while (!glfwWindowShouldClose(glfwGetCurrentContext()))
	{
		UpdateDrawFrame();
	}
	#endif
	
	Engine::DeleteEngineInstance();
	Audio::Instance()->Clear();

	return 0;
}

void UpdateDrawFrame() {
	Engine::Instance()->UpdateEngine();
}
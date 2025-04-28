#include "Assets.h"
#include <string>

const char* Assets::bip_sound = "assets/Sounds/sound.wav";

void Assets::LoadAssets()
{

	#ifdef __EMSCRIPTEN__
	// Load shaders
	ResourceManager::LoadShader("assets/Shaders23/SpriteRendererVS.glsl", "assets/Shaders23/SpriteRendererFS.glsl", spriteShader);
	#else
	ResourceManager::LoadShader("assets/Shaders46/SpriteRendererVS.glsl", "assets/Shaders46/SpriteRendererFS.glsl", spriteShader);
	#endif

	// Load textures
	ResourceManager::LoadTexture("assets/Textures/example_spritesheet.png", playerTexture);
	ResourceManager::LoadTexture("assets/Textures/image.png", playerTexture2);
	ResourceManager::LoadTexture("assets/Textures/Health bar.png", healthBarTexture);
	ResourceManager::LoadTexture("assets/Textures/Current health.png", currentHealthTexture);

	ResourceManager::LoadTexture("assets/Buttons/Play Button.png", playButton);
	ResourceManager::LoadTexture("assets/Buttons/Quit Button.png", quitButton);
	
	ResourceManager::LoadTexture("assets/Buttons/Yes Button.png", yesButton);
	ResourceManager::LoadTexture("assets/Buttons/No Button.png", noButton);
	ResourceManager::LoadTexture("assets/Text Images/Quit Confirmation Text.png", quitConfirmationText);

	// Load music
	ma_sound* default_music = ResourceManager::LoadMusic("assets/Music/Anxiety.wav", anxietyMusic);
	Audio::Instance()->PlayMusic(default_music);
	ma_sound_set_volume(default_music, 0.15f);
}
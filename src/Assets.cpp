#include "Assets.h"

void Assets::LoadAssets()
{
	// Load shaders
	ResourceManager::LoadShader("SpriteRendererVS.glsl", "SpriteRendererFS.glsl", spriteShader);

	// Load textures
	ResourceManager::LoadTexture("Textures/example_spritesheet.png", playerTexture);
	ResourceManager::LoadTexture("Textures/image.png", playerTexture2);
	ResourceManager::LoadTexture("Textures/Health bar.png", healthBarTexture);
	ResourceManager::LoadTexture("Textures/Current health.png", currentHealthTexture);

	ResourceManager::LoadTexture("Buttons/Play Button.png", playButton);
	ResourceManager::LoadTexture("Buttons/Quit Button.png", quitButton);
	
	ResourceManager::LoadTexture("Buttons/Yes Button.png", yesButton);
	ResourceManager::LoadTexture("Buttons/No Button.png", noButton);
	ResourceManager::LoadTexture("Text Images/Quit Confirmation Text.png", quitConfirmationText);

	// Load music
	ma_sound* default_music = ResourceManager::LoadMusic("Music/Anxiety.wav", anxietyMusic);
	Audio::Instance()->PlayMusic(default_music);
	ma_sound_set_volume(default_music, 0.15f);
}
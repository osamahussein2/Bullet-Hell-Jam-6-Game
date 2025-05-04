#include "Assets.h"
#include "OptionsMenu.h"
#include <string>

//const char* Assets::bip_sound = "assets/Sounds/sound.wav";

float Assets::musicVolume = 0.15f;
float Assets::sfxVolume = 1.0f;

void Assets::LoadAssets()
{

	#ifdef __EMSCRIPTEN__
	// Load shaders
	ResourceManager::LoadShader("assets/Shaders23/SpriteRendererVS.glsl", "assets/Shaders23/SpriteRendererFS.glsl", spriteShader);
	#else
	ResourceManager::LoadShader("assets/Shaders46/SpriteRendererVS.glsl", "assets/Shaders46/SpriteRendererFS.glsl", spriteShader);
	#endif

	// Load textures
	ResourceManager::LoadTexture("assets/Text Images/text_atlas.png", textAtlas);
	ResourceManager::LoadTexture("assets/Buttons/button.png", buttonTexture);
	ResourceManager::LoadTexture("assets/Textures/Slider bar.png", sliderBarTexture);

	ResourceManager::LoadTexture("assets/Textures/Player.png", playerTexture);
	ResourceManager::LoadTexture("assets/Textures/Health bar.png", healthBarTexture);
	ResourceManager::LoadTexture("assets/Textures/Current health.png", currentHealthTexture);

	ResourceManager::LoadTexture("assets/Textures/PlayerBullet.png", playerBulletTexture);
	ResourceManager::LoadTexture("assets/Textures/EnemyBullet.png", enemyBulletTexture);

	ResourceManager::LoadTexture("assets/Textures/bomba.png", bombaTexture);
	ResourceManager::LoadTexture("assets/Textures/cultistBasic.png", cultistBasicTexture);
	ResourceManager::LoadTexture("assets/Textures/Aura bar.png", auraBarTexture);
	ResourceManager::LoadTexture("assets/Textures/Aura UI.png", auraUITexture);
	ResourceManager::LoadTexture("assets/Textures/Score UI.png", scoreUITexture);
	
	// Load music
	ma_sound* default_music = ResourceManager::LoadMusic("assets/Music/Anxiety.wav", anxietyMusic);
	Audio::Instance()->PlayMusic(default_music);
	ma_sound_set_volume(default_music, musicVolume);

	// Load sounds
	ResourceManager::LoadSound("assets/Sounds/sound.wav", buttonHoverSound);
	ma_sound_set_volume(ResourceManager::GetSound(buttonHoverSound), sfxVolume);
}
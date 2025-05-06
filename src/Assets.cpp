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
	ResourceManager::LoadTexture("assets/Textures/summoner.png", summonerTexture);
	ResourceManager::LoadTexture("assets/Textures/orb.png", orbTexture);

	ResourceManager::LoadTexture("assets/Textures/Aura bar.png", auraBarTexture);
	ResourceManager::LoadTexture("assets/Textures/Aura UI.png", auraUITexture);
	ResourceManager::LoadTexture("assets/Textures/Score UI.png", scoreUITexture);

	ResourceManager::LoadTexture("assets/Textures/progress_bar_unit.png", progressBarUnit);
	ResourceManager::LoadTexture("assets/Textures/progress_bar_unit_boss.png", progressBarBoss);
	ResourceManager::LoadTexture("assets/Textures/progress_bar_point.png", progressBarPoint);

	ResourceManager::LoadTexture("assets/Textures/enemyHealthBar.png", enemyHealthTexture);
	ResourceManager::LoadTexture("assets/Textures/beholder.png", beholderTexture);
	
	// Debug textures
	ResourceManager::LoadTexture("assets/Debug/circle.png", circleTexture);
	ResourceManager::LoadTexture("assets/Debug/rectangle.png", rectangleTexture);

	// Load music
	ResourceManager::LoadMusic("assets/Music/Anxiety.wav", anxietyMusic);
	ResourceManager::LoadMusic("assets/Music/LTHAWFD.wav", LTHAWFD);
	ResourceManager::StartMusic(anxietyMusic);
	//Audio::Instance()->PlayMusic(default_music);
	//ma_sound_set_volume(default_music, musicVolume);

	// Load sounds
	ResourceManager::LoadSound("assets/Sounds/sound.wav", buttonHoverSound);
	ResourceManager::GetSound(buttonHoverSound)->SetVolume(sfxVolume);
}
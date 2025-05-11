#include "Game.h"
#include "Window.h"
#include "PauseMenu.h"
#include "Audio.h"
#include "Input.h"
#include "Assets.h"
#include "TextRenderer.h"
#include "BackgroundRenderer.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Summoner.h"
#include "Effect.h"

Game* Game::gameInstance = nullptr;


Game::Game() : playerAura(1.0f), maxPlayerAura(1.0f), timer(0.0f), progress()
{
}

Game::~Game()
{
	gameInstance = nullptr;

	Clear();
}

Game* Game::Instance()
{
	if (gameInstance == nullptr)
	{
		gameInstance = new Game();
		return gameInstance;
	}

	return gameInstance;
}

void Game::InitializeGame()
{
	// nothing here lol, cuz the game loaded only when play pressed
	// so that the music is started correctly
}

void Game::UpdateGame(float deltaTime_)
{
	if (canFinish) {
		progress.GoNext();
		LoadGame();
	}

	progress.Update(deltaTime_);
	
	score++;
	player->Update(deltaTime_);

	// Clamp the player's position to not exceed the game's size

	HandleCollisions(deltaTime_);

	for (auto it = enemies.begin(); it != enemies.end(); ) {
		auto enemy = *it;
		enemy->Update(deltaTime_);
		if (enemy->destroyed) {
			delete enemy;
			it = enemies.erase(it);
		} else {
			++it;
		}
	}

	enemies.insert(enemies.end(), new_enemies.begin(), new_enemies.end());
	new_enemies.clear();

	for (auto it = playerBullets.begin(); it != playerBullets.end(); ) {
		auto bullet = *it;
		bullet->Update(deltaTime_);
		if (bullet->destroyed) {
			delete bullet;
			it = playerBullets.erase(it);
		} else {
			++it;
		}
	}

	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
		auto bullet = *it;
		bullet->Update(deltaTime_);
		if (bullet->destroyed) {
			delete bullet;
			it = enemyBullets.erase(it);
		} else {
			++it;
		}
	}

	for (auto it = effects.begin(); it != effects.end(); ) {
		auto effect = *it;
		effect->Update(deltaTime_);
		if (effect->destroyed) {
			delete effect;
			it = effects.erase(it);
		} else {
			++it;
		}
	}

	playerAura = glm::clamp(playerAura, 0.f, maxPlayerAura);
	if (playerAura == 0.0f) {
		Window::Instance()->state = GAME_OVER;
		LoadGame();
		ResourceManager::StopMusic();
	}

	// Change the current aura bar size in x coordinate depending on player's current aura value
	HUDs[1].position.x = HUDs[1].size.x * playerAura / maxPlayerAura - HUDs[1].size.x;

	// UI updating

	for (UserInterface& hud : HUDs)
	{
		hud.Update(true);
	}

	for (UserInterface& bar : progressBarUnits)
	{
		bar.Update(true);
	}

	Debug::Instance()->Update();
}

void Game::HandleInput(float deltaTime_)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE)){
		Audio::Instance()->PlaySound(Assets::buttonHoverSound);
	}

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		Window::Instance()->state = PAUSE_MENU;
		ResourceManager::StopMusic();
	}

	if (Input::IsKeyPressed(GLFW_KEY_P))
	{
		if (enemies.size()>0) KillAllEnemies();
		else progress.currentLevel->GetCurrentStage()->timer = 27.7;
	}
}

void Game::RenderGame(float deltaTime_)
{
	/***********************************************************************/
	float winW = Window::Instance()->GetWindowWidth();
	float winH = Window::Instance()->GetWindowHeight();

	vec2 arena = progress.currentLevel->GetCurrentStage()->arenaSize;
	float gameW = arena.x;
	float gameH = arena.y;

	float game_aspect = gameW/gameH;
	
	float viewW = std::min(winW, winH * game_aspect);
	float viewH = viewW / game_aspect;

	float x_diff = winW-viewW;
	float y_diff = winH-viewH;
	
	float x = x_diff/2.f;
	float y = y_diff/2.f;
	
	glViewport(0, 0, winW, winH);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_SCISSOR_TEST);
	#ifdef __EMSCRIPTEN__ // on web just take the whole screen
	glScissor(0, 0, winW, winH);
	glViewport(0, 0, winW, winH);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	#else
	glScissor(x, y, viewW, viewH);
	glViewport(x, y, viewW, viewH);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	#endif
	glDisable(GL_SCISSOR_TEST);
	/***********************************************************************/

	auto projection = ortho(0.0f, gameW,
		gameH, 0.0f,
		-1.0f, 1.0f);

	// set uniforms for sprite rendering shader
	glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);
	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	//set uniforms for background rendering shader
	glUseProgram(ResourceManager::GetShader(Assets::backgroundShader).shaderProgram);
	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::backgroundShader).shaderProgram, "spriteImage"), 0);
	glUniform1f(glGetUniformLocation(ResourceManager::GetShader(Assets::backgroundShader).shaderProgram, "time"), progress.currentLevel->GetCurrentStage()->timer);
	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::backgroundShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	timer += deltaTime_;

	BackgroundRenderer::Instance()->DrawBackground(vec2(gameW, gameH));

	player->Draw();

	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}

	for (Bullet* bullet : playerBullets) {
		bullet->Draw();
	}

	for (Bullet* bullet : enemyBullets) {
		bullet->Draw();
	}

	for (Effect* effect : effects) {
		effect->Draw();
	}

	
	for (UserInterface& aura : HUDs)
	{
		aura.Draw(*UserInterface::UiRendererInstance());
	}
	
	
	DrawProgressBar();

	vec2 gSize = Window::Instance()->GetGameSize();
	TextRenderer::Instance()->DrawTextFromRight(std::to_string(score).c_str(), vec2(gSize.x-10, gSize.y-8), 0.8, true, vec3(0.0));
}

void Game::HandleCollisions(float deltaTime_)
{
	for (Enemy* enemy : enemies) {
		for (Bullet* bullet : playerBullets) {
			enemy->CollideWith(bullet);
		}
		enemy->CollideWith(player);
	}

	for (Bullet* bullet : enemyBullets) {
		player->CollideWith(bullet);
	}
}

void Game::LoadGame()
{
	Clear();
	canFinish = false;
	player = new Player(vec2(0.0));

	progress.Load();

	vec2 gSize = Window::Instance()->GetGameSize();

	// Aura UI
	HUDs.push_back(UserInterface(vec2(0.0, gSize.y-32), vec2(96, 32), Assets::auraUITexture, Assets::spriteShader, vec3(1.0), true));
	// Current aura bar
	HUDs.push_back(UserInterface(vec2(0.0, gSize.y-8), vec2(80, 8), Assets::auraBarTexture, Assets::spriteShader, vec3(1.0), true));
	// Score UI
	HUDs.push_back(UserInterface(vec2(gSize.x-96, gSize.y-32), vec2(96, 32), Assets::scoreUITexture, Assets::spriteShader, vec3(1.0), true));
	
	progressBarUnits.push_back(UserInterface(vec2(0, 6), vec2(48, 24), Assets::progressBarUnit, Assets::spriteShader, vec3(1.0), true));
	progressBarUnits.push_back(UserInterface(vec2(0, 6), vec2(48, 24), Assets::progressBarBoss, Assets::spriteShader, vec3(1.0), true));
	progressBarUnits.push_back(UserInterface(vec2(0, 6), vec2(24, 24), Assets::progressBarPoint, Assets::spriteShader, vec3(1.0), true));
	
	playerAura = maxPlayerAura;
}

void Game::Clear()
{
	if (player) delete player;
	for (Bullet* bullet : playerBullets) {
		delete bullet;
	}
	playerBullets.clear();
	for (Bullet* bullet : enemyBullets) {
		delete bullet;
	}
	enemyBullets.clear();

	ClearEnemies();

	for (Effect* effect : effects) {
		delete effect;
	}
	effects.clear();

	HUDs.clear();
	progressBarUnits.clear();
}

void Game::DeleteGameInstance()
{
	if (gameInstance){
		delete gameInstance;
		gameInstance = nullptr;
	}
	else {
		std::cerr<<"gameInstance is not valid to delete\n";
	}
}

void Game::DrawProgressBar()
{
	int siz = progress.currentLevel->stages.size();
	vec2 gSize = ArenaSize();
	float rel_off_x = progressBarUnits[0].size.x/gSize.x;
	
	float rel_center = 0.5;
	float l = rel_off_x*siz;
	float start_x = rel_center-l/2;
	
	for (int i = 0; i < siz; i++) {
		if (i < siz-1) {
			progressBarUnits[0].Draw(
				*UserInterface::UiRendererInstance(),
				vec2(rel_off_x*i+start_x, 0),
				true
			);
		}
		else {
			progressBarUnits[1].Draw(
				*UserInterface::UiRendererInstance(),
				vec2(rel_off_x*i+start_x, 0),
				true
			);
		}
	}

	int cur = progress.currentLevel->currentStage;
	float unot_off = 8.f * float(cur != siz-1) / gSize.x;

	progressBarUnits[2].Draw(
		*UserInterface::UiRendererInstance(),
		vec2(rel_off_x*cur+start_x+unot_off, 0),
		true
	);
	

}

void Game::ClearEnemies() {
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();

	for (Enemy* enemy : new_enemies) {
		delete enemy;
	}
	new_enemies.clear();
}

void Game::KillAllEnemies() {
	for (auto enemy : enemies) {
		enemy->Die();
	}
}

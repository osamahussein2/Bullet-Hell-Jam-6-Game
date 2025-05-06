#include "Game.h"
#include "Window.h"
#include "PauseMenu.h"
#include "Audio.h"
#include "Input.h"
#include "Assets.h"
#include "TextRenderer.h"

#include "Bullet.h"
#include "Enemy.h"

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
	LoadGame();
}

void Game::UpdateGame(float deltaTime_)
{
	score++;
	player->Update(deltaTime_);

	// Clamp the player's position to not exceed the game's size
	player->position.x = glm::clamp(player->position.x, -10.0f, Window::Instance()->GetGameSize().x - 50.0f);
	player->position.y = glm::clamp(player->position.y, 0.0f, Window::Instance()->GetGameSize().y - 50.0f);

	HandleCollisions(deltaTime_);

	for (Enemy* enemy : enemies) {
		enemy->Update(deltaTime_);
	}

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


	// UI drawing

	for (UserInterface& hud : HUDs)
	{
		hud.Update(true);
	}

	// Change the current aura bar size in x coordinate depending on player's current aura value
	HUDs[1].rel_pos.x = HUDs[1].rel_size.x * playerAura / maxPlayerAura - HUDs[1].rel_size.x;
	
	if (playerAura <= 0.0f) {
		playerAura = 0.0f;
		Window::Instance()->state = GAME_OVER;
	}
	else {
		//playerAura -= 0.1 * deltaTime_;
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
	}

	if (Input::IsKeyPressed(GLFW_KEY_P))
	{
		progress.GoNext();
		LoadGame();
	}
}

void Game::RenderGame(float deltaTime_)
{
	/***********************************************************************/
	float winW = Window::Instance()->GetWindowWidth();
	float winH = Window::Instance()->GetWindowHeight();

	
	float gameW = Window::Instance()->GetGameSize().x;
	float gameH = Window::Instance()->GetGameSize().y;

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

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	timer += deltaTime_;

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
		
	
	for (UserInterface& aura : HUDs)
	{
		aura.Draw(*UserInterface::UiRendererInstance());
	}
	
	vec2 gSize = Window::Instance()->GetGameSize();
	TextRenderer::Instance()->DrawTextFromRight(std::to_string(score).c_str(), vec2(gSize.x-10, gSize.y-8), 0.8, true, vec3(0.0));
	//HUDs[2].Draw(*UserInterface::UiRendererInstance());
}

void Game::HandleCollisions(float deltaTime_)
{
	for (Bullet* bullet : playerBullets) {
		for (Enemy* enemy : enemies) {
			enemy->CollideWith(bullet);
		}	
	}

	for (Bullet* bullet : enemyBullets) {
		player->CollideWith(bullet);
	}
}

void Game::LoadGame()
{
	Clear();
	
	player = new Player(vec2(0.0));

	vec2 gSize = Window::Instance()->GetGameSize();
	// Aura UI
	HUDs.push_back(UserInterface(vec2(0.0, -32), vec2(96, 32), Assets::auraUITexture, Assets::spriteShader, vec3(1.0), true));
	// Current aura bar
	HUDs.push_back(UserInterface(vec2(0.0, -8), vec2(80, 8), Assets::auraBarTexture, Assets::spriteShader, vec3(1.0), true));
	// Score UI
	HUDs.push_back(UserInterface(vec2(gSize.x-96, -32), vec2(96, 32), Assets::scoreUITexture, Assets::spriteShader, vec3(1.0), true));

	playerAura = maxPlayerAura;

	progress.Load();
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

	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();

	HUDs.clear();
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

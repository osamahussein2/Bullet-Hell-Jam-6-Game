#include "Game.h"
#include "Window.h"
#include "PauseMenu.h"
#include "Audio.h"
#include "Input.h"
#include "Assets.h"

#include "Bullet.h"
#include "Enemy.h"

Game* Game::gameInstance = nullptr;


Game::Game() : playerHealth(200.0f), maxPlayerHealth(200.0f), timer(0.0f)
{
}

Game::~Game()
{
	gameInstance = nullptr;

	delete player;

	for (Bullet* bullet : playerBullets) {
		delete bullet;
	}

	for (Bullet* bullet : enemyBullets) {
		delete bullet;
	}

	for (Enemy* enemy : enemies) {
		delete enemy;
	}

	healthBars.clear();
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
	player = new Player(vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2));
	player->position -= player->size*vec2(0.5);

	enemies.push_back(new Bomba(player->position + vec2(-100, -50)));
	enemies.push_back(new CultistBasic(player->position + vec2(100, -50)));

	// Health bar UI
	healthBars.push_back(UserInterface(vec2(0.0, 0.0), vec2(0.3f, 0.1f), Assets::healthBarTexture, Assets::spriteShader));

	// Current health UI
	healthBars.push_back(UserInterface(vec2(0.0, 0.0), vec2(0.3f, 0.1f), Assets::currentHealthTexture, Assets::spriteShader));
}

void Game::UpdateGame(float deltaTime_)
{
	player->Update(deltaTime_);

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


	for (UserInterface& healthbar : healthBars){
		healthbar.Update(true);
	}
	healthBars[1].size.x *= float(playerHealth) / float(maxPlayerHealth);

	
	if (playerHealth <= 0.0f)
	{
		playerHealth = 0.0f;

		Window::Instance()->state = GAME_OVER;
	}
	else
	{
		//playerHealth -= 1.0f * deltaTime_;

		if (playerHealth >= 132.0f)
		{
			// Make the health bar green
			healthBars[1].color = vec3(0.0f, 1.0f, 0.0f);
		}

		else if (playerHealth >= 66.0f)
		{
			// Make the health bar yellow
			healthBars[1].color = vec3(1.0f, 1.0f, 0.0f);
		}

		else if (playerHealth < 66.0f)
		{
			// Make the health bar red
			healthBars[1].color = vec3(1.0f, 0.0f, 0.0f);
		}
	}
		
}

void Game::HandleInput(float deltaTime_)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE)){
		Audio::Instance()->PlaySound(Assets::bip_sound);
	}

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		Window::Instance()->state = PAUSE_MENU;
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
	glClearColor(1,1,1,1);
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

	for (Bullet* bullet : playerBullets) {
		bullet->Draw();
	}

	for (Bullet* bullet : enemyBullets) {
		bullet->Draw();
	}

	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}

	for (UserInterface& healthbar : healthBars){
		healthbar.Draw(*UserInterface::UiRendererInstance());
	}
		
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

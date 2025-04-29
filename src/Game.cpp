#include "Game.h"
#include "Window.h"
#include "PauseMenu.h"
#include "Audio.h"
#include "Input.h"
#include "Assets.h"

Game* Game::gameInstance = nullptr;


Game::Game() : playerHealth(200.0f), maxPlayerHealth(200.0f), timer(0.0f)
{
}

Game::~Game()
{
	gameInstance = nullptr;

	delete playerSpriteRenderer;
	delete player;

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
	// Set render-specific controls
	playerSpriteRenderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
	
	playerSpriteRenderer->GetAnimationHandler()->AddAnimation(AnimationData{
		8, // columns
		15, // rows
		1, // y_pos
		6, // frames
		12.f // fps
		}
	);
	
	playerSpriteRenderer->GetAnimationHandler()->AddAnimation(AnimationData{
		8, // columns
		15, // rows
		2, // y_pos
		6, // frames
		12.f // fps
		}
	);

	playerSpriteRenderer->GetAnimationHandler()->AddAnimation(AnimationData{
		8, // columns
		15, // rows
		0, // y_pos
		8, // frames
		12.f // fps
		}
	);	

	player = new GameObject(vec2(600.0f, 100.0f), vec2(100.0f, 100.0f), Assets::playerTexture, vec3(1.0f),
		vec2(0.0f, 0.0f));

	// Health bar UI
	healthBars.push_back(UserInterface(vec2(0.0, 0.0), vec2(0.3f, 0.1f), Assets::healthBarTexture, Assets::spriteShader));

	// Current health UI
	healthBars.push_back(UserInterface(vec2(0.0, 0.0), vec2(0.3f, 0.1f), Assets::currentHealthTexture, Assets::spriteShader));
}

void Game::UpdateGame(float deltaTime_)
{
	player->position += player->velocity * deltaTime_;
	
	if (player->velocity.x < 0){
		playerSpriteRenderer->SetHorFlip(true);
	}
	else if (player->velocity.x > 0){
		playerSpriteRenderer->SetHorFlip(false);
	}

	// player animation
	playerSpriteRenderer->UpdateAnimation(deltaTime_);
	Animation* player_anim = playerSpriteRenderer->GetAnimationHandler();
	if (Input::IsKeyPressed(GLFW_KEY_SPACE)){ // just to switch animations
		player_anim->SetCurrentAnim( (player_anim->GetCurrentAnim()+1) % player_anim->GetNumberOfAnims());
	}

	for (UserInterface& healthbar : healthBars){
		healthbar.Update(true);
	}
	healthBars[1].size.x *= float(playerHealth) / float(maxPlayerHealth);

	
	if (playerHealth <= 0.0f)
	{
		playerHealth = 0.0f;
	}
	else
	{
		playerHealth -= 1.0f * deltaTime_;

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

	vec2 direction = vec2(0.0f);
	// Move the player around the game

	if (Input::IsKeyDown(GLFW_KEY_W) || Input::IsKeyDown(GLFW_KEY_UP)) {
		direction.y = -1.0f;
	}

	if (Input::IsKeyDown(GLFW_KEY_S) || Input::IsKeyDown(GLFW_KEY_DOWN)) {
		direction.y = 1.0f;
	}

	if (Input::IsKeyDown(GLFW_KEY_A) || Input::IsKeyDown(GLFW_KEY_LEFT)) {
		direction.x = -1.0f;
	}

	if (Input::IsKeyDown(GLFW_KEY_D) || Input::IsKeyDown(GLFW_KEY_RIGHT)) {
		direction.x = 1.0f;
	}

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		Window::Instance()->state = PAUSE_MENU;
	}

	if (direction != vec2(0.f)) direction = normalize(direction);
	float speed = 450.f;
	player->velocity = direction * speed;
}

void Game::RenderGame(float deltaTime_)
{
	//glViewport(0,0,Window::Instance()->GetWindowWidth(),Window::Instance()->GetWindowHeight());


	/***********************************************************************/
	float winW = Window::Instance()->GetWindowWidth();
	float winH = Window::Instance()->GetWindowHeight();

	float gameW = 1600;
	float gameH = 900;

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
	glScissor(x, y, viewW, viewH);
	glViewport(x, y, viewW, viewH);
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glDisable(GL_SCISSOR_TEST);
	/***********************************************************************/

	auto projection = ortho(0.0f, gameW,
		gameH, 0.0f,
		-1.0f, 1.0f);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	timer += deltaTime_;

	playerSpriteRenderer->DrawSprite(player->sprite, player->position, player->size,
		player->rotation, player->color);


	for (UserInterface& healthbar : healthBars){
		healthbar.Draw(*UserInterface::UiRendererInstance());
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

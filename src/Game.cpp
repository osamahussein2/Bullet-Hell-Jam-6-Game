#include "Game.h"
#include "Window.h"
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

	delete playerSpriteRenderer, player;

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
		healthbar.Update();
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
		Audio::Instance()->PlaySound("Sounds/sound.wav");
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

	if (direction != vec2(0.f)) direction = normalize(direction);
	float speed = 450.f;
	player->velocity = direction * speed;
}

void Game::RenderGame(float deltaTime_)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(),
		(float)Window::Instance()->GetWindowHeight(), 0.0f,
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

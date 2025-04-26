#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Assets.h"

Game* Game::gameInstance = nullptr;

mat4 nothing = mat4(0.0f);

Game::Game() : playerHealth(200.0f), timer(0.0f), projection(nothing)
{
}

Game::~Game()
{
	gameInstance = nullptr;

	delete playerSpriteRenderer, player;

	if (!healthSpriteRenderers.empty())
	{
		healthSpriteRenderers.clear();
		healthSpriteRenderers = vector<SpriteRenderer*>(); // Deallocate the memory of this vector
	}

	if (!healthBars.empty())
	{
		healthBars.clear();
		healthBars = vector<UserInterface*>(); // Deallocate the memory of this vector
	}
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
	playerSpriteRenderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, true);
	
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

	healthSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false));
	healthSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false));

	// Configure shaders
	projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(), 0.0f, 
		(float)Window::Instance()->GetWindowHeight(), -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"), 
		1, GL_FALSE, value_ptr(projection));

	player = new GameObject(vec2(600.0f, 100.0f), vec2(100.0f, 100.0f), ResourceManager::GetTexture(Assets::playerTexture), vec3(1.0f),
		vec2(0.0f, 0.0f));

	// Health bar UI
	healthBars.push_back(new UserInterface(vec2(10.0f, 850.0f), vec2(200.0f, 25.0f), ResourceManager::GetTexture(Assets::healthBarTexture), vec3(1.0f)));

	// Current health UI
	healthBars.push_back(new UserInterface(vec2(10.0f, 850.0f), vec2(200.0f, 25.0f), ResourceManager::GetTexture(Assets::currentHealthTexture), vec3(1.0f)));
}

void Game::UpdateGame(float deltaTime_)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(), 0.0f,
		(float)Window::Instance()->GetWindowHeight(), -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	healthBars[0]->position = vec2(10.0f, Window::Instance()->GetWindowHeight() - 50.0f);
	healthBars[1]->position = vec2(10.0f, Window::Instance()->GetWindowHeight() - 50.0f);

	player->position += player->velocity * deltaTime_;
	
	// player animation
	playerSpriteRenderer->UpdateAnimation(deltaTime_);
	Animation* player_anim = playerSpriteRenderer->GetAnimationHandler();
	if (Input::IsKeyPressed(GLFW_KEY_SPACE)){ // just to switch animations
		player_anim->SetCurrentAnim( (player_anim->GetCurrentAnim()+1) % player_anim->GetNumberOfAnims());
	}

	healthBars[1]->size.x = playerHealth;

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
			healthBars[1]->color = vec3(0.0f, 1.0f, 0.0f);
		}

		else if (playerHealth >= 66.0f)
		{
			// Make the health bar yellow
			healthBars[1]->color = vec3(1.0f, 1.0f, 0.0f);
		}

		else if (playerHealth < 66.0f)
		{
			// Make the health bar red
			healthBars[1]->color = vec3(1.0f, 0.0f, 0.0f);
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
		direction.y = 1.0f;
	}

	if (Input::IsKeyDown(GLFW_KEY_S) || Input::IsKeyDown(GLFW_KEY_DOWN)) {
		direction.y = -1.0f;
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
	timer += deltaTime_;

	playerSpriteRenderer->DrawSprite(player->sprite, player->position, player->size,
		player->rotation, player->color);

	healthSpriteRenderers[0]->DrawSprite(ResourceManager::GetTexture(Assets::healthBarTexture), healthBars[0]->position, 
		healthBars[0]->size, 0.0f, healthBars[0]->color);

	healthSpriteRenderers[1]->DrawSprite(ResourceManager::GetTexture(Assets::currentHealthTexture), healthBars[1]->position, 
		healthBars[1]->size, 0.0f, healthBars[1]->color);

	//player->DrawSprite(*playerSpriteRenderer);

	for (unsigned int i = 0; i < healthBars.size(); i++)
	{
		for (unsigned int j = 0; j < healthSpriteRenderers.size(); j++)
		{
			healthBars[i]->DrawSprite(*healthSpriteRenderers[j]);
		}
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

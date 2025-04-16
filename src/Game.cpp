#include "Game.h"
#include "Window.h"

Game* Game::gameInstance = nullptr;

Game::Game() : gameWidth(1200.0f), gameHeight(900.0f), playerHealth(200.0f)
{
}

Game::~Game()
{
	delete gameInstance, playerSpriteRenderer, player;

	healthSpriteRenderers.clear();
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
	// Load shaders
	ResourceManager::LoadShader("SpriteRendererVS.glsl", "SpriteRendererFS.glsl", spriteShader);

	// Load textures
	ResourceManager::LoadTexture("Textures/player.png", playerTexture);
	ResourceManager::LoadTexture("Textures/Health bar.png", healthBarTexture);
	ResourceManager::LoadTexture("Textures/Current health.png", currentHealthTexture);

	// Set render-specific controls
	playerSpriteRenderer = new SpriteRenderer(ResourceManager::GetShader(spriteShader));

	healthSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader)));
	healthSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader)));

	// Configure shaders
	mat4 projection = ortho(0.0f, gameWidth, 0.0f, gameHeight, -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "projectionMatrix"), 
		1, GL_FALSE, value_ptr(projection));

	player = new GameObject(vec2(gameWidth / 2, 100.0f), vec2(100.0f, 100.0f), ResourceManager::GetTexture(playerTexture), vec3(1.0f),
		vec2(0.0f, 0.0f));

	// Health bar UI
	healthBars.push_back(new UserInterface(vec2(10.0f, 850.0f), vec2(200.0f, 25.0f), ResourceManager::GetTexture(healthBarTexture), vec3(1.0f)));

	// Current health UI
	healthBars.push_back(new UserInterface(vec2(10.0f, 850.0f), vec2(200.0f, 25.0f), ResourceManager::GetTexture(currentHealthTexture), vec3(1.0f)));
}

void Game::UpdateGame(float deltaTime_)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	player->position += player->velocity * deltaTime_;

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
	vec2 direction = vec2(0.0f);
	// Move the player around the game
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		direction.y = 1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		direction.y = -1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		direction.x = -1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		direction.x = 1.0f;
	}

	// Don't move the player around once the player releases the WASD or arrow keys
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_RELEASE)
	{
		direction = vec2(0.0f);
	}

	if (direction != vec2(0.f)) direction = normalize(direction);
	float speed = 450.f;
	player->velocity = direction * speed;
}

void Game::RenderGame(float deltaTime_)
{
	playerSpriteRenderer->DrawSprite(ResourceManager::GetTexture(playerTexture), player->position, player->size, player->rotation, player->color);

	healthSpriteRenderers[0]->DrawSprite(ResourceManager::GetTexture(healthBarTexture), healthBars[0]->position, healthBars[0]->size, 0.0f, healthBars[0]->color);

	healthSpriteRenderers[1]->DrawSprite(ResourceManager::GetTexture(currentHealthTexture), healthBars[1]->position, healthBars[1]->size, 0.0f, healthBars[1]->color);

	player->DrawSprite(*playerSpriteRenderer);

	for (unsigned int i = 0; i < healthBars.size(); i++)
	{
		for (unsigned int j = 0; j < healthSpriteRenderers.size(); j++)
		{
			healthBars[i]->DrawSprite(*healthSpriteRenderers[j]);
		}
	}
}
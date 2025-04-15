#include "Game.h"
#include "Window.h"

Game* Game::gameInstance = nullptr;

Game::Game() : gameWidth(1200.0f), gameHeight(900.0f)
{
}

Game::~Game()
{
	delete gameInstance, playerSpriteRenderer, player;
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

	// Set render-specific controls
	playerSpriteRenderer = new SpriteRenderer(ResourceManager::GetShader(spriteShader));

	// Configure shaders
	mat4 projection = ortho(0.0f, gameWidth, 0.0f, gameHeight, -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "projectionMatrix"), 
		1, GL_FALSE, value_ptr(projection));

	player = new GameObject(vec2(gameWidth / 2, 100.0f), vec2(100.0f, 100.0f), ResourceManager::GetTexture(playerTexture), vec3(1.0f),
		vec2(0.0f, 0.0f));
}

void Game::UpdateGame(float deltaTime_)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	player->position += player->velocity * deltaTime_;
}

void Game::HandleInput(float deltaTime_)
{
	// Move the player around the game
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		player->velocity.y = 1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		player->velocity.y = -1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		player->velocity.x = -1.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player->velocity.x = 1.0f;
	}

	// Don't move the player around once the player releases the WASD or arrow keys
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
		glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_RELEASE && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_RELEASE)
	{
		player->velocity = vec2(0.0f);
	}
}

void Game::RenderGame(float deltaTime_)
{
	playerSpriteRenderer->DrawSprite(ResourceManager::GetTexture(playerTexture), player->position, player->size, player->rotation, player->color);

	player->DrawSprite(*playerSpriteRenderer);
}
#include "Game.h"

Game* Game::gameInstance = nullptr;

Game::Game()
{
}

Game::~Game()
{
	delete gameInstance, spriteRenderer, player;
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
	ResourceManager::LoadTexture("Textures/image.png", playerTexture);

	// Set render-specific controls
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader(spriteShader));

	// Configure shaders
	mat4 projection = ortho(0.0f, 1200.0f, 0.0f, 900.0f, -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "projectionMatrix"), 
		1, GL_FALSE, value_ptr(projection));

	player = new GameObject(vec2(50.0f, 100.0f), vec2(0.1f), ResourceManager::GetTexture(playerTexture), vec3(1.0f),
		vec2(1.0f, 1.0f));
}

void Game::UpdateGame(float deltaTime_)
{
}

void Game::HandleInput()
{
}

void Game::RenderGame(float deltaTime_)
{
	spriteRenderer->DrawSprite(ResourceManager::GetTexture(playerTexture), vec2(0.0f, 0.0f),
		vec2(1200, 900), 0.0f, vec3(1.0));

	player->DrawSprite(*spriteRenderer);
}
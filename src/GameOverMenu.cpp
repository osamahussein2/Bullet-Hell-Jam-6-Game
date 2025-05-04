#include "GameOverMenu.h"
#include "Window.h"
#include "Assets.h"
#include "TextRenderer.h"
#include "Game.h"

GameOverMenu* GameOverMenu::gameOverMenuInstance = nullptr;

GameOverMenu::GameOverMenu() : Menu()
{

}

GameOverMenu::~GameOverMenu()
{
	gameOverMenuInstance = nullptr;

	buttons.clear();
}

GameOverMenu* GameOverMenu::Instance()
{
	if (gameOverMenuInstance == nullptr)
	{
		gameOverMenuInstance = new GameOverMenu();
		return gameOverMenuInstance;
	}

	return gameOverMenuInstance;
}

void GameOverMenu::InitializeMenu()
{

	vec2 rel_text_size = vec2(0.6, 0.2);
	vec2 rel_pos = vec2((1 - rel_text_size.x) / 2.f, 0.05);

	vec2 rel_size = vec2(0.3, 0.2);
	float vert_padd = 0.1; // padding
	rel_pos.x = (1 - rel_size.x) / 2.f;
	rel_pos.y += rel_text_size.y + vert_padd;

	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "restart"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "quit"));

	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void GameOverMenu::UpdateMenu()
{

	// update buttons
	for (Button& btn : buttons) {
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Game::Instance()->playerHealth = Game::Instance()->maxPlayerHealth;
		Game::Instance()->playerAura = Game::Instance()->maxPlayerAura;

		Window::Instance()->state = GAME;
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = MAIN_MENU;
	}
}

void GameOverMenu::RenderMenu()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Render the quit confirmation text
	// update projection
	auto projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(),
		(float)Window::Instance()->GetWindowHeight(), 0.0f,
		-1.0f, 1.0f);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));


	for (Button& btn : buttons) {
		btn.Draw(*UserInterface::UiRendererInstance());
	}

	TextRenderer::Instance()->DrawTextRelCent("game over", vec2(0.5, 0.1), 0.004);
}

void GameOverMenu::DeleteGameOverMenuInstance()
{
	if (gameOverMenuInstance) {
		delete gameOverMenuInstance;
		gameOverMenuInstance = nullptr;
	}
	else {
		std::cerr << "gameOverMenuInstance is not valid to delete\n";
	}
}
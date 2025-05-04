#include "MainMenu.h"
#include "Window.h"
#include "Assets.h"
#include "Game.h"

MainMenu* MainMenu::mainMenuInstance = nullptr;

MainMenu::MainMenu() : Menu()
{
}

MainMenu::~MainMenu()
{
	mainMenuInstance = nullptr;
	buttons.clear();
}

MainMenu* MainMenu::Instance()
{
	if (mainMenuInstance == nullptr)
	{
		mainMenuInstance = new MainMenu();
		return mainMenuInstance;
	}

	return mainMenuInstance;
}

void MainMenu::InitializeMenu()
{
	vec2 rel_size = vec2(0.25, 0.15);
	float vert_padd = 0.05;
	vec2 rel_pos = vec2((1-rel_size.x)/2.f, 0.2);

	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "play"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "options"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "credits"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "quit"));
	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void MainMenu::UpdateMenu()
{
	// update buttons
	for (Button& btn : buttons){
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Game::Instance()->LoadGame();
		Window::Instance()->state = GAME;
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = OPTIONS_MENU;
	}
	if (buttons[2].GetState() == BTN_HOVERED && buttons[2].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = CREDITS_MENU;
	}
	if (buttons[3].GetState() == BTN_HOVERED && buttons[3].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = QUIT_CONF;
	}
	//text_r.UpdateAnimation(1.0/60);
}

void MainMenu::RenderMenu()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// update projection
	auto projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(), 
	(float)Window::Instance()->GetWindowHeight(), 0.0f,
	-1.0f, 1.0f);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	for (Button& btn : buttons){
		btn.Draw(*UserInterface::UiRendererInstance());
	}
	
}

void MainMenu::DeleteMainMenuInstance()
{
	if (mainMenuInstance){
		delete mainMenuInstance;
		mainMenuInstance = nullptr;
	}
	else {
		std::cerr<<"mainMenuInstance is not valid to delete\n";
	}
}

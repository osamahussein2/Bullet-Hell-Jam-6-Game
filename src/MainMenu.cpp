#include "MainMenu.h"
#include "Window.h"
#include "Assets.h"

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
	vec2 rel_size = vec2(0.4, 0.2);
	float vert_padd = 0.1;
	vec2 rel_pos = vec2((1-rel_size.x)/2.f, 0.2);

	buttons.push_back(Button(rel_pos, rel_size, Assets::playButton, Assets::spriteShader));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::quitButton, Assets::spriteShader));
	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void MainMenu::UpdateMenu()
{
	// update buttons
	for (Button& btn : buttons){
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = GAME;
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = QUIT_CONF;
	}

	// Releasing the ESCAPE key will not register a key press anymore
	if (Input::IsKeyReleased(GLFW_KEY_ESCAPE) && Window::Instance()->keyRegistered)
	{
		Window::Instance()->keyRegistered = false;
	}

	// Pressing the ESCAPE key will also take the player to the quit confirmation screen
	else if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) && !Window::Instance()->keyRegistered)
	{
		Window::Instance()->state = QUIT_CONF;

		Window::Instance()->keyRegistered = true;
	}
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

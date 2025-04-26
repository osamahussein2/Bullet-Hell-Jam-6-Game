#include "QuitConfirmationMenu.h"
#include "Window.h"
#include "Assets.h"

QuitConfirmationMenu* QuitConfirmationMenu::quitConfirmationMenuInstance = nullptr;

mat4 nothingInQuitPrompt = mat4(0.0f);

QuitConfirmationMenu::QuitConfirmationMenu() : Menu()
{

}

QuitConfirmationMenu::~QuitConfirmationMenu()
{
	quitConfirmationMenuInstance = nullptr;

	buttons.clear();
	texts.clear();
}

QuitConfirmationMenu* QuitConfirmationMenu::Instance()
{
	if (quitConfirmationMenuInstance == nullptr)
	{
		quitConfirmationMenuInstance = new QuitConfirmationMenu();
		return quitConfirmationMenuInstance;
	}

	return quitConfirmationMenuInstance;
}

void QuitConfirmationMenu::InitializeMenu()
{
	
	vec2 rel_text_size = vec2(0.6, 0.2);
	vec2 rel_pos = vec2((1-rel_text_size.x)/2.f, 0.05);
	texts.push_back(UserInterface(rel_pos, rel_text_size, Assets::quitConfirmationText, Assets::spriteShader));

	vec2 rel_size = vec2(0.3, 0.2);
	float vert_padd = 0.1; // padding
	rel_pos.x = (1-rel_size.x)/2.f;
	rel_pos.y += rel_text_size.y + vert_padd;

	buttons.push_back(Button(rel_pos, rel_size, Assets::yesButton, Assets::spriteShader));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::noButton, Assets::spriteShader));
	
	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void QuitConfirmationMenu::UpdateMenu()
{
	
	// update buttons
	for (Button& btn : buttons){
		btn.Update();
	}
	
	for (UserInterface& text : texts){
		text.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = MAIN_MENU;
	}

	// Pressing the ESCAPE key will also quit the game
	if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}
}

void QuitConfirmationMenu::RenderMenu()
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


	for (Button& btn : buttons){
		btn.Draw(*UserInterface::UiRendererInstance());
	}

	for (UserInterface& text : texts){
		text.Draw(*UserInterface::UiRendererInstance());
	}
}

void QuitConfirmationMenu::DeleteQuitConfirmationMenuInstance()
{
	if (quitConfirmationMenuInstance){
		delete quitConfirmationMenuInstance;
		quitConfirmationMenuInstance = nullptr;
	}
	else {
		std::cerr<<"quitConfirmationMenuInstance is not valid to delete\n";
	}
}

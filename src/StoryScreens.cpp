#include "StoryScreens.h"
#include "Window.h"

IntroMenu* IntroMenu::introMenuInstance = nullptr;

IntroMenu::IntroMenu() : Menu()
{
}

IntroMenu::~IntroMenu()
{
	introMenuInstance = nullptr;
	buttons.clear();
}

IntroMenu* IntroMenu::Instance()
{
	if (introMenuInstance == nullptr)
	{
		introMenuInstance = new IntroMenu();
		return introMenuInstance;
	}

	return introMenuInstance;
}

void IntroMenu::DeleteMainMenuInstance()
{
    	if (introMenuInstance){
		delete introMenuInstance;
		introMenuInstance = nullptr;
	}
	else {
		std::cerr<<"introMenuInstance is not valid to delete\n";
	}
}

void IntroMenu::InitializeMenu()
{
	vec2 rel_size = vec2(0.2, 0.1);
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.8);
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "next"));

    an_text.text = "the evil cult tries todestabilize world's   aura you have to stop them";

}

void IntroMenu::UpdateMenu(float deltaTime)
{
    an_text.Update(deltaTime);
	for (Button& btn : buttons) {
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
        Window::Instance()->state = GAME;
    }
}

void IntroMenu::RenderMenu()
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

    for (Button& btn : buttons) {
        btn.Draw(*UserInterface::UiRendererInstance());
    }

    TextRenderer::Instance()->DrawTextRelWrap(
        an_text.GetCurrentText().c_str(), vec2(0.1, 0.05), vec2(0.8, 0.8), 0.0045, vec3(0.8941176470588236, 0, 0.34509803921568627)
    );
}

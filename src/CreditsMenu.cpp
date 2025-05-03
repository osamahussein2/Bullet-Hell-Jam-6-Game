#include "CreditsMenu.h"
#include "Window.h"

CreditsMenu* CreditsMenu::creditsMenuInstance = nullptr;

float lastCreditsFrame = 0.f;

CreditsMenu::CreditsMenu() : Menu(), creditsTime(0.0f), timeShouldIncrease(true)
{
}

CreditsMenu::~CreditsMenu()
{
	creditsMenuInstance = nullptr;
	buttons.clear();
}

CreditsMenu* CreditsMenu::Instance()
{
	if (creditsMenuInstance == nullptr)
	{
		creditsMenuInstance = new CreditsMenu();
		return creditsMenuInstance;
	}

	return creditsMenuInstance;
}

void CreditsMenu::InitializeMenu()
{
	vec2 rel_size = vec2(0.3, 0.15);
	float vert_padd = 0.15;
	float hori_padd = 0.1;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.5);

	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::button, Assets::spriteShader, "back"));

	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void CreditsMenu::UpdateMenu()
{
	// update buttons
	for (Button& btn : buttons) {
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = MAIN_MENU;
	}

	//text_r.UpdateAnimation(1.0/60);
}

void CreditsMenu::RenderMenu()
{
	float currentCreditsFrame = glfwGetTime(); // Get the current time

	// deltaTime is the time between current frame and last frame
	float creditsDeltaTime = currentCreditsFrame - lastCreditsFrame;
	lastCreditsFrame = currentCreditsFrame;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// update projection
	auto projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(),
		(float)Window::Instance()->GetWindowHeight(), 0.0f,
		-1.0f, 1.0f);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	TextRenderer::Instance()->DrawTextRelCent("credits menu", vec2(0.5, 0.05), 0.002);

	TextRenderer::Instance()->DrawTextRelCent("programmers", vec2(0.4, 0.2), 0.0015, vec3(creditsTime, 0.0, 0.0));

	TextRenderer::Instance()->DrawTextRelCent("duyha", vec2(0.6, 0.2), 0.0015, vec3(creditsTime, 0.0, 0.0));
	TextRenderer::Instance()->DrawTextRelCent("osama hussein", vec2(0.648, 0.27), 0.0015, vec3(creditsTime, 0.0, 0.0));

	TextRenderer::Instance()->DrawTextRelCent("artist", vec2(0.43, 0.4), 0.0015, vec3(0.0, creditsTime, 0.0));
	TextRenderer::Instance()->DrawTextRelCent("whoobadedo", vec2(0.63, 0.4), 0.0015, vec3(0.0, creditsTime, 0.0));

	TextRenderer::Instance()->DrawTextRelCent("sound/music composers", vec2(0.34, 0.6), 0.0015, vec3(0.0, creditsTime, creditsTime));
	TextRenderer::Instance()->DrawTextRelCent("mesiosaki", vec2(0.625, 0.6), 0.0015, vec3(0.0, creditsTime, creditsTime));
	TextRenderer::Instance()->DrawTextRelCent("antman242", vec2(0.625, 0.67), 0.0015, vec3(0.0, creditsTime, creditsTime));

	ChangeTextColorOvertime(creditsDeltaTime);

	for (Button& btn : buttons) {
		btn.Draw(*UserInterface::UiRendererInstance());
	}

}

void CreditsMenu::DeleteCreditsMenuInstance()
{
	if (creditsMenuInstance) 
	{
		delete creditsMenuInstance;
		creditsMenuInstance = nullptr;
	}
	else {
		std::cerr << "creditsMenuInstance is not valid to delete\n";
	}
}

void CreditsMenu::ChangeTextColorOvertime(float deltaTime_)
{
	// Increment the credits time once time should increase is true
	if (timeShouldIncrease)
	{
		creditsTime += deltaTime_;
	}

	// Decrement the credits time once time should increase is false
	else if (!timeShouldIncrease)
	{
		creditsTime -= deltaTime_;

		// Make sure the credits time isn't greater than 1 when time is decrementing so that the colors will change faster
		if (creditsTime >= 1.0f)
		{
			creditsTime = 1.0f;
		}
	}

	// Set time should increase to false once the credits time reaches the max time
	if (creditsTime >= timerReachesMaxTime)
	{
		timeShouldIncrease = false;
	}

	// Set time should increase back to true once the credits time reaches zero
	else if (creditsTime <= timerReachesZero)
	{
		timeShouldIncrease = true;
	}
}
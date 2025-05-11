#include "OptionsMenu.h"
#include "Window.h"

OptionsMenu* OptionsMenu::optionsMenuInstance = nullptr;

OptionsMenu::OptionsMenu() : Menu(), mousePressedOnMusicSlider(false), lastMusicSliderHandlePosition(NULL), 
mousePressedOnSFXSlider(false), lastSFXSliderHandlePosition(NULL)
{
}

OptionsMenu::~OptionsMenu()
{
	optionsMenuInstance = nullptr;
	buttons.clear();
	sliderBars.clear();
	sliderHandles.clear();
}

OptionsMenu* OptionsMenu::Instance()
{
	if (optionsMenuInstance == nullptr)
	{
		optionsMenuInstance = new OptionsMenu();
		return optionsMenuInstance;
	}

	return optionsMenuInstance;
}

void OptionsMenu::InitializeMenu()
{
	vec2 rel_size = vec2(0.2, 0.1);
	float vert_padd = 0.1;
	float hori_padd = 0.1;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.45);

	vert_padd = 0.35f;
	rel_pos.y += rel_size.y - vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "fullscreen"));

	vert_padd = 0.45f;
	rel_size = vec2(0.3, 0.15);
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "back"));

	InitializeSliderBars();
	InitializeSliderHandles();

	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void OptionsMenu::UpdateMenu()
{
	// update buttons
	for (Button& btn : buttons) {
		btn.Update();
	}

	for (UserInterface& sliderbar : sliderBars) {
		sliderbar.Update();
	}

	for (UserInterface& sliderhandle : sliderHandles) {
		sliderhandle.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
#ifndef __EMSCRIPTEN__
		Window::Instance()->ToggleFullscreen();
#endif
	}

	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {

		if (Window::Instance()->prevState == MAIN_MENU)
		{
			Window::Instance()->state = MAIN_MENU;
		}

		else if (Window::Instance()->prevState == PAUSE_MENU)
		{
			Window::Instance()->state = PAUSE_MENU;
		}
	}

	ModifyMusicSliderHandle();
	ModifySFXSliderHandle();

	ResourceManager::ApplyMusicVolume(Assets::musicVolume);
	ResourceManager::ApplySfxVolume(Assets::sfxVolume);

	RestrictMusicSliderHandlePosition();
	RestrictSFXSliderHandlePosition();
}

void OptionsMenu::RenderMenu()
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

	TextRenderer::Instance()->DrawTextRelCent("options menu", vec2(0.5, 0.1), 0.004, vec3(0.8941176470588236, 0, 0.34509803921568627));

	TextRenderer::Instance()->DrawTextRelCent("music volume", vec2(0.4, 0.38), 0.0015);
	TextRenderer::Instance()->DrawTextRelCent("sfx volume", vec2(0.4, 0.52), 0.0015);

	TextRenderer::Instance()->DrawTextRelCent("sfx volume", vec2(0.4, 0.52), 0.0015);

	for (UserInterface& sliderbar : sliderBars) {
		sliderbar.Draw(*UserInterface::UiRendererInstance()
	);
	}

	for (UserInterface& sliderhandle : sliderHandles) {
		sliderhandle.Draw(*UserInterface::UiRendererInstance(),
		vec2(-sliderHandles[0].rel_size.x/2, 0.0)
		);
	}

	for (Button& btn : buttons) {
		btn.Draw(*UserInterface::UiRendererInstance());
	}
}

void OptionsMenu::DeleteOptionsMenuInstance()
{
	if (optionsMenuInstance) {
		delete optionsMenuInstance;
		optionsMenuInstance = nullptr;
	}
	else {
		std::cerr << "OptionsMenuInstance is not valid to delete\n";
	}
}

void OptionsMenu::InitializeSliderBars()
{
	vec2 rel_size = vec2(0.25, 0.1);
	float vert_padd = 0.1;
	float hori_padd = 0.1;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.75);

	// Slider bar 1's position and size
	rel_pos.x += rel_size.x - hori_padd;

	vert_padd = 0.4;
	rel_size = vec2(0.3, 0.025);

	rel_pos.y += rel_size.y - vert_padd;

	sliderBars.push_back(UserInterface(rel_pos, rel_size, Assets::sliderBarTexture,
		Assets::spriteShader, vec3(1.0f)));

	// Slider bar 2's position and size
	hori_padd = 0.3;
	rel_pos.x -= rel_size.x - hori_padd;

	vert_padd = 0.1;

	rel_pos.y += rel_size.y + vert_padd;

	sliderBars.push_back(UserInterface(rel_pos, rel_size, Assets::sliderBarTexture,
		Assets::spriteShader, vec3(1.0f)));
}

void OptionsMenu::InitializeSliderHandles()
{
	vec2 rel_size = vec2(0.02, 0.05);

	sliderHandles.push_back(UserInterface(
		sliderBars[0].rel_pos+vec2(sliderBars[0].rel_size.x*Assets::musicVolume, -sliderBars[0].rel_size.y/2),
		rel_size, Assets::sliderHandleTexture,
		Assets::spriteShader, vec3(1.0)));
	
	lastMusicSliderHandlePosition = sliderHandles[0].rel_pos.x;

	sliderHandles.push_back(UserInterface(
		sliderBars[1].rel_pos+vec2(sliderBars[1].rel_size.x*Assets::sfxVolume, -sliderBars[1].rel_size.y/2),
		rel_size, Assets::sliderHandleTexture,
		Assets::spriteShader, vec3(1.0)));
	
	lastSFXSliderHandlePosition = sliderHandles[1].rel_pos.x;
}

void OptionsMenu::RestrictMusicSliderHandlePosition()
{
	//float w = Window::Instance()->GetWindowWidth();
	float start = sliderBars[0].rel_pos.x;
	float end = sliderBars[0].rel_pos.x+sliderBars[0].rel_size.x;

	lastMusicSliderHandlePosition = glm::clamp(
		lastMusicSliderHandlePosition,
		start, end
	);
	sliderHandles[0].rel_pos.x = lastMusicSliderHandlePosition;
	Assets::musicVolume = (sliderHandles[0].rel_pos.x-start)/(end-start);
}

void OptionsMenu::RestrictSFXSliderHandlePosition()
{
	float start = sliderBars[1].rel_pos.x;
	float end = sliderBars[1].rel_pos.x+sliderBars[1].rel_size.x;
	
	lastSFXSliderHandlePosition = glm::clamp(
		lastSFXSliderHandlePosition,
		start, end
	);
	sliderHandles[1].rel_pos.x = lastSFXSliderHandlePosition;
	Assets::sfxVolume = (sliderHandles[1].rel_pos.x-start)/(end-start);
}

void OptionsMenu::ModifyMusicSliderHandle()
{
	if (mousePressedOnMusicSlider == true)
	{
		lastMusicSliderHandlePosition = Window::Instance()->GetMousePositionX()/Window::Instance()->GetWindowWidth();
		sliderHandles[0].rel_pos.x = lastMusicSliderHandlePosition;
	}
	else
	{
		if (lastMusicSliderHandlePosition != NULL)
		{
			sliderHandles[0].rel_pos.x = lastMusicSliderHandlePosition;
		}
	}

	auto siz = Window::Instance()->GetWindowSize();
	// Update the slider handle based on position
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX()/siz.x >= sliderHandles[0].rel_pos.x-sliderHandles[0].rel_size.x*0.5f &&
		Window::Instance()->GetMousePositionX()/siz.x <= sliderHandles[0].rel_pos.x+sliderHandles[0].rel_size.x*0.5f &&
		Window::Instance()->GetMousePositionY()/siz.y >= sliderHandles[0].rel_pos.y &&
		Window::Instance()->GetMousePositionY()/siz.y <= sliderHandles[0].rel_pos.y + sliderHandles[0].rel_size.y)
	{
		mousePressedOnMusicSlider = true;
	}

	else
	{
		mousePressedOnMusicSlider = false;
	}
}

void OptionsMenu::ModifySFXSliderHandle()
{
	if (mousePressedOnSFXSlider == true)
	{
		lastSFXSliderHandlePosition = Window::Instance()->GetMousePositionX()/Window::Instance()->GetWindowWidth();
		sliderHandles[1].rel_pos.x = lastSFXSliderHandlePosition;
	}

	else
	{
		if (lastSFXSliderHandlePosition != NULL)
		{
			sliderHandles[1].rel_pos.x = lastSFXSliderHandlePosition;
		}
	}

	auto siz = Window::Instance()->GetWindowSize();
	// Update the slider handle based on position
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX()/siz.x >= sliderHandles[1].rel_pos.x-sliderHandles[1].rel_size.x*0.5f &&
		Window::Instance()->GetMousePositionX()/siz.x <= sliderHandles[1].rel_pos.x+sliderHandles[1].rel_size.x*0.5f &&
		Window::Instance()->GetMousePositionY()/siz.y >= sliderHandles[1].rel_pos.y &&
		Window::Instance()->GetMousePositionY()/siz.y <= sliderHandles[1].rel_pos.y + sliderHandles[1].rel_size.y)
	{
		mousePressedOnSFXSlider = true;
	}

	else
	{
		mousePressedOnSFXSlider = false;
	}
}

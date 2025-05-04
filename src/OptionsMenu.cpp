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
		Window::Instance()->state = MAIN_MENU;
	}

	ModifyMusicSliderHandle();
	ModifySFXSliderHandle();

	//ma_sound_set_volume(ResourceManager::GetMusic(Assets::anxietyMusic), Assets::musicVolume);
	ResourceManager::ApplyMusicVolume(Assets::musicVolume);
	ResourceManager::ApplySfxVolume(Assets::sfxVolume);
	//ma_sound_set_volume(ResourceManager::GetSound(Assets::buttonHoverSound), Assets::sfxVolume);

	RestrictMusicSliderHandlePosition();
	RestrictSFXSliderHandlePosition();

	//text_r.UpdateAnimation(1.0/60);
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

	TextRenderer::Instance()->DrawTextRelCent("options menu", vec2(0.5, 0.1), 0.004);

	TextRenderer::Instance()->DrawTextRelCent("music volume", vec2(0.4, 0.38), 0.0015);
	TextRenderer::Instance()->DrawTextRelCent("sfx volume", vec2(0.4, 0.52), 0.0015);

	TextRenderer::Instance()->DrawTextRelCent("sfx volume", vec2(0.4, 0.52), 0.0015);

	for (UserInterface& sliderbar : sliderBars) {
		sliderbar.Draw(*UserInterface::UiRendererInstance());
	}

	for (UserInterface& sliderhandle : sliderHandles) {
		sliderhandle.Draw(*UserInterface::UiRendererInstance());
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
	vec2 rel_size = vec2(0.3, 0.15);
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
	float vert_padd = 0.1;
	float hori_padd = 0.1;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.0f, 0.75);

	// Slider handle 1's position and size
	hori_padd = 0.325f;
	rel_pos.x += rel_size.x + hori_padd;

	vert_padd = 0.435;
	rel_pos.y += rel_size.y - vert_padd;

	sliderHandles.push_back(UserInterface(rel_pos, rel_size, Assets::sliderBarTexture,
		Assets::spriteShader, vec3(0.5f)));

	// Slider handle 2's position and size
	rel_pos = vec2((1 - rel_size.x) / 2.0f, 0.85);
	hori_padd = 0.325f;
	rel_pos.x += rel_size.x + hori_padd;

	vert_padd = 0.41f;
	rel_pos.y += rel_size.y - vert_padd;

	sliderHandles.push_back(UserInterface(rel_pos, rel_size, Assets::sliderBarTexture,
		Assets::spriteShader, vec3(0.5f)));
}

void OptionsMenu::RestrictMusicSliderHandlePosition()
{
	// Restrict the player from going past the music volume slider bar
	if (sliderHandles[0].position.x > Window::Instance()->GetWindowWidth() / 1.19760479042f)
	{
		lastMusicSliderHandlePosition = Window::Instance()->GetWindowWidth() / 1.19760479042f;
		sliderHandles[0].position.x = Window::Instance()->GetWindowWidth() / 1.19760479042f;
	}

	else if (sliderHandles[0].position.x < Window::Instance()->GetWindowWidth() / 1.82857142857f)
	{
		lastMusicSliderHandlePosition = Window::Instance()->GetWindowWidth() / 1.82857142857f;
		sliderHandles[0].position.x = Window::Instance()->GetWindowWidth() / 1.82857142857f;

		Assets::musicVolume = 0.0f;
	}

	// If the slider handle is between the slider bar, change the volume based on the value
	else if (sliderHandles[0].position.x > Window::Instance()->GetWindowWidth() / 1.82857142857f &&
		sliderHandles[0].position.x <= Window::Instance()->GetWindowWidth() / 1.19760479042f)
	{
		// Update the music volume based on the music volume slider handle value
		Assets::musicVolume = ((sliderHandles[0].position.x - Window::Instance()->GetWindowWidth() / 1.82857142857f)
			/ (Window::Instance()->GetWindowWidth() / 1.19760479042f)) * maxMusicVolumeThreshold;
	}
}

void OptionsMenu::RestrictSFXSliderHandlePosition()
{
	// Restrict the player from going past the SFX volume slider bar
	if (sliderHandles[1].position.x > Window::Instance()->GetWindowWidth() / 1.19760479042f)
	{
		Assets::sfxVolume = 1.0f;

		lastSFXSliderHandlePosition = Window::Instance()->GetWindowWidth() / 1.19760479042f;
		sliderHandles[1].position.x = Window::Instance()->GetWindowWidth() / 1.19760479042f;
	}

	else if (sliderHandles[1].position.x < Window::Instance()->GetWindowWidth() / 1.82857142857f)
	{
		lastSFXSliderHandlePosition = Window::Instance()->GetWindowWidth() / 1.82857142857f;
		sliderHandles[1].position.x = Window::Instance()->GetWindowWidth() / 1.82857142857f;

		Assets::sfxVolume = 0.0f;
	}

	// If the slider handle is between the slider bar, change the volume based on the value
	else if (sliderHandles[1].position.x > Window::Instance()->GetWindowWidth() / 1.82857142857f &&
		sliderHandles[1].position.x <= Window::Instance()->GetWindowWidth() / 1.19760479042f)
	{
		// Update the music volume based on the music volume slider handle value
		Assets::sfxVolume = ((sliderHandles[1].position.x - Window::Instance()->GetWindowWidth() / 1.82857142857f) / 
			Window::Instance()->GetWindowWidth() / 1.19760479042f) * maxSFXVolumeThreshold;
	}
}

void OptionsMenu::ModifyMusicSliderHandle()
{
	if (mousePressedOnMusicSlider == true)
	{
		lastMusicSliderHandlePosition = Window::Instance()->GetMousePositionX();
		sliderHandles[0].position.x = lastMusicSliderHandlePosition;
	}

	else
	{
		if (lastMusicSliderHandlePosition != NULL)
		{
			sliderHandles[0].position.x = lastMusicSliderHandlePosition;
		}
	}

	// Update the slider handle based on position
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= sliderHandles[0].position.x &&
		Window::Instance()->GetMousePositionX() <= sliderHandles[0].position.x + sliderHandles[0].size.x &&
		Window::Instance()->GetMousePositionY() >= sliderHandles[0].position.y &&
		Window::Instance()->GetMousePositionY() <= sliderHandles[0].position.y + sliderHandles[0].size.y)
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
		lastSFXSliderHandlePosition = Window::Instance()->GetMousePositionX();
		sliderHandles[1].position.x = lastSFXSliderHandlePosition;
	}

	else
	{
		if (lastSFXSliderHandlePosition != NULL)
		{
			sliderHandles[1].position.x = lastSFXSliderHandlePosition;
		}
	}

	// Update the slider handle based on position
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= sliderHandles[1].position.x &&
		Window::Instance()->GetMousePositionX() <= sliderHandles[1].position.x + sliderHandles[1].size.x &&
		Window::Instance()->GetMousePositionY() >= sliderHandles[1].position.y &&
		Window::Instance()->GetMousePositionY() <= sliderHandles[1].position.y + sliderHandles[1].size.y)
	{
		mousePressedOnSFXSlider = true;
	}

	else
	{
		mousePressedOnSFXSlider = false;
	}
}

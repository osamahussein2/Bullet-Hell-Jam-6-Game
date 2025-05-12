#ifndef STORY_H
#define STORY_H

#include "Menu.h"
#include "ResourceManager.h"
#include "UserInterface.h"
#include "Input.h"

#include "TextRenderer.h"

#include <vector>

class IntroMenu : public Menu
{
public:
	virtual ~IntroMenu();

	static IntroMenu* Instance();
	static void DeleteMainMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
    IntroMenu();

    AnimatedText an_text;

	static IntroMenu* introMenuInstance;
};

class OutroMenu : public Menu
{
public:
	virtual ~OutroMenu();

	static OutroMenu* Instance();
	static void DeleteMainMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
    OutroMenu();

    AnimatedText an_text;

	static OutroMenu* outroMenuInstance;
};

#endif
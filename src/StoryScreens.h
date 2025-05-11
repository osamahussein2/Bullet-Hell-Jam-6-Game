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
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
    IntroMenu();

	static IntroMenu* introMenuInstance;
};

#endif
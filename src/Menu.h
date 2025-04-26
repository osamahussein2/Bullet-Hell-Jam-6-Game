#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <vector>

class Menu
{
protected:
	Menu() {}
	virtual ~Menu() {}

	virtual void InitializeMenu() = 0;
	virtual void UpdateMenu() = 0;
	virtual void RenderMenu() = 0;

	std::vector<Button> buttons = {};
};

#endif
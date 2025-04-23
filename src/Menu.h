#ifndef MENU_H
#define MENU_H

class Menu
{
protected:
	Menu() {}
	virtual ~Menu() {}

	virtual void InitializeMenu() = 0;
	virtual void UpdateMenu() = 0;
	virtual void RenderMenu() = 0;
};

#endif
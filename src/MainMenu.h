#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include "TextRenderer.h"

#include <vector>

class MainMenu : public Menu
{
public:
	virtual ~MainMenu();

	static MainMenu* Instance();
	static void DeleteMainMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
	MainMenu();

	static MainMenu* mainMenuInstance;
};
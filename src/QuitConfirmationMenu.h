#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include <vector>

class QuitConfirmationMenu : public Menu
{
public:
	virtual ~QuitConfirmationMenu();

	static QuitConfirmationMenu* Instance();
	static void DeleteQuitConfirmationMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
	QuitConfirmationMenu();

	static QuitConfirmationMenu* quitConfirmationMenuInstance;
};

class QuitToMainMenuConfirmationMenu : public Menu
{
public:
	virtual ~QuitToMainMenuConfirmationMenu();

	static QuitToMainMenuConfirmationMenu* Instance();
	static void DeleteQuitToMainMenuConfirmationMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
	QuitToMainMenuConfirmationMenu();

	static QuitToMainMenuConfirmationMenu* quitToMainMenuConfirmationMenuInstance;
};
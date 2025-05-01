#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include <vector>

class PauseMenu : public Menu
{
public:
	virtual ~PauseMenu();

	static PauseMenu* Instance();
	static void DeletePauseMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	PauseMenu();

	static PauseMenu* pauseMenuInstance;
};
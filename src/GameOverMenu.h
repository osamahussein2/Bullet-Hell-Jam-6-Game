#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include <vector>

class GameOverMenu : public Menu
{
public:
	virtual ~GameOverMenu();

	static GameOverMenu* Instance();
	static void DeleteGameOverMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	GameOverMenu();

	static GameOverMenu* gameOverMenuInstance;
};
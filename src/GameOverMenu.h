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
	GameOverMenu();
	
	static GameOverMenu* Instance();
	static void DeleteGameOverMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:

	static GameOverMenu* gameOverMenuInstance;
};
#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include <vector>

class MainMenu : public Menu
{
public:
	virtual ~MainMenu();

	static MainMenu* Instance();

	virtual void InitializeMenu();
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	MainMenu();

	static MainMenu* mainMenuInstance;

	vector<UserInterface*> buttons;
	vector<SpriteRenderer*> buttonSpriteRenderers;

	enum ShaderMapNumbers
	{
		spriteShader = 0
	};

	enum TextureMapNumbers
	{
		playButton = 0,
		quitButton = 1
	};

	float gameWidth, gameHeight;
};
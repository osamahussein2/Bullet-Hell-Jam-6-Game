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
	static void DeleteMainMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	MainMenu();

	static MainMenu* mainMenuInstance;

	vector<UserInterface*> buttons;
	vector<SpriteRenderer*> buttonSpriteRenderers;

	mat4& projection;

	bool shaderIsCurrentlyUsed;

	const vec2 initialButtonSize = vec2(0.2, 0.2f); // relative to window size
};
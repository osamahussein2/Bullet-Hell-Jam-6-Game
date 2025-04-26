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
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	QuitConfirmationMenu();

	static QuitConfirmationMenu* quitConfirmationMenuInstance;

	vector<UserInterface*> buttons;
	vector<SpriteRenderer*> buttonSpriteRenderers;

	vector<UserInterface*> texts;
	vector<SpriteRenderer*> textSpriteRenderers;

	mat4& projection;

	bool shaderIsCurrentlyUsed;

	const vec2 initialQuitConfirmationTextSize = vec2(0.5f, 0.2f);
	const vec2 initialButtonSize = vec2(0.2, 0.2f); // relative to window size
};
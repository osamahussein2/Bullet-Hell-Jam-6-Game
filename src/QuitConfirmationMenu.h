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

	enum ShaderMapNumbers
	{
		spriteShader = 0
	};

	enum TextureMapNumbers
	{
		yesButton = 0,
		noButton = 1,
		quitConfirmationText = 2
	};

	bool shaderIsCurrentlyUsed;

	const vec2& initialQuitConfirmationTextSize = vec2(500.0f, 50.0f);
	const vec2& initialButtonSize = vec2(100.0f, 50.0f);
};
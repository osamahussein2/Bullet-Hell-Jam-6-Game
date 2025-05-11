#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include "TextRenderer.h"
#include "UserInterface.h"

#include <vector>

class CreditsMenu : public Menu
{
public:
	virtual ~CreditsMenu();

	static CreditsMenu* Instance();
	static void DeleteCreditsMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu(float deltaTime);
	virtual void RenderMenu();

private:
	CreditsMenu();
	
	static CreditsMenu* creditsMenuInstance;

	bool timeShouldIncrease;

	const float timerReachesZero = 0.0f;
	const float timerReachesMaxTime = 3.0f;
};
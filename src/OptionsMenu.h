#include "Menu.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "UserInterface.h"
#include "Input.h"

#include "TextRenderer.h"
#include "UserInterface.h"

#include <vector>

class OptionsMenu : public Menu
{
public:
	virtual ~OptionsMenu();

	static OptionsMenu* Instance();
	static void DeleteOptionsMenuInstance();

	virtual void InitializeMenu();
	virtual void UpdateMenu();
	virtual void RenderMenu();

private:
	OptionsMenu();

	void InitializeSliderBars();
	void InitializeSliderHandles();

	void RestrictMusicSliderHandlePosition();
	void RestrictSFXSliderHandlePosition();

	void ModifyMusicSliderHandle();
	void ModifySFXSliderHandle();

	static OptionsMenu* optionsMenuInstance;

	vector<UserInterface> sliderBars;
	vector<UserInterface> sliderHandles;

	bool mousePressedOnMusicSlider;
	bool mousePressedOnSFXSlider;

	float lastMusicSliderHandlePosition;
	float lastSFXSliderHandlePosition;
};
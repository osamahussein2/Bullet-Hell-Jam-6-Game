#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "UserInterface.h"

#include <vector>

class Game
{
public:
	~Game();

	static Game* Instance();
	static void DeleteGameInstance();

	void InitializeGame();
	void UpdateGame(float deltaTime_);
	void HandleInput(float deltaTime_);
	void RenderGame(float deltaTime_);
	void RenderHUD(float deltaTime_);

private:
	Game();

	static Game* gameInstance;

	SpriteRenderer* playerSpriteRenderer;

	GameObject* player;

	vector<UserInterface> healthBars = {};

	int maxPlayerHealth;
	int playerHealth;

	float timer;
};


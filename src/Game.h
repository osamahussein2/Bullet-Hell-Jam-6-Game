#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Player.h"

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

	int playerHealth;
	const int maxPlayerHealth;

private:
	Game();

	static Game* gameInstance;

	Player* player;

	vector<UserInterface> healthBars = {};

	float timer;
};


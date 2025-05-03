#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Player.h"

#include <vector>
#include "Bullet.h"

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

	std::vector<Bullet*> playerBullets;

private:
	Game();

	static Game* gameInstance;

	Player* player;

	vector<UserInterface> healthBars = {};

	int maxPlayerHealth;
	int playerHealth;

	float timer;
};


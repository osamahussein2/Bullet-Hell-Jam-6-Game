#include "ResourceManager.h"
#include <vector>

#include "Player.h"
#include "UserInterface.h"
#include "Progress.h"

// forward declarations
class Bullet;
class Enemy;

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

	void HandleCollisions(float deltaTime_);

	void LoadGame();
	void Clear();

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;

	int score = 1;
	
	float playerAura;
	const float maxPlayerAura;

	Player* player;

	Progress progress;

private:
	Game();

	static Game* gameInstance;

	vector<UserInterface> HUDs = {};

	float timer;
};


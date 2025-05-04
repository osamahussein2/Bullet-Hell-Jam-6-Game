#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Player.h"

#include <vector>

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

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;
	int playerHealth;
	const int maxPlayerHealth;

private:
	Game();

	static Game* gameInstance;

	Player* player;

	vector<UserInterface> healthBars = {};

	float timer;
};


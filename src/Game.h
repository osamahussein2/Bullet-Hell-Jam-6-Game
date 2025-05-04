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

	void LoadGame();
	void Clear();

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;

	int score = 1;
	
	float playerAura;
	const float maxPlayerAura;

	Player* player;

private:
	Game();

	static Game* gameInstance;

	vector<UserInterface> HUDs = {};

	float timer;
};


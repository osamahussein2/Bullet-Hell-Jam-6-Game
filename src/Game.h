#include "ResourceManager.h"
#include <vector>

#include "Player.h"
#include "UserInterface.h"
#include "Progress.h"

// forward declarations
class Bullet;
class Enemy;
class Effect;

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

	std::vector<Enemy*> enemies = {};
	/*
	if enemies spawn other enemies, in update loop the vector is gonna grow and at some point reach new allocation
	(initially vector is bigger than required, so it won't trigger right away)
	which invalidates itrators, so the program crashes if you add enemies into the vector right away
	the same thing has to be done if bullets spawn other bullets etc.
	*/
	std::vector<Enemy*> new_enemies = {};

	std::vector<Bullet*> playerBullets = {};
	std::vector<Bullet*> enemyBullets = {};
	std::vector<Effect*> effects = {};

	vec2 ArenaSize() {return progress.currentLevel->GetCurrentStage()->arenaSize; }

	int score = 1;
	
	float playerAura;
	const float maxPlayerAura;

	Player* player = nullptr;

	Progress progress;

	bool canFinish = false;

	void ClearEnemies();
	void KillAllEnemies();

	private:
	Game();

	void DrawProgressBar();

	static Game* gameInstance;

	vector<UserInterface> HUDs = {};
	vector<UserInterface> progressBarUnits = {};

	float timer;
};


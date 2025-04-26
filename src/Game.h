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

private:
	Game();

	static Game* gameInstance;

	SpriteRenderer* playerSpriteRenderer;
	vector<SpriteRenderer*> healthSpriteRenderers;

	GameObject* player;

	vector<UserInterface*> healthBars;

	mat4& projection;

	int playerHealth;

	float timer;
};


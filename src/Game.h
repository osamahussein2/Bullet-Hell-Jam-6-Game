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

	int playerHealth;

	enum ShaderMapNumbers
	{
		spriteShader = 0
	};

	enum TextureMapNumbers
	{
		playerTexture = 0,
		healthBarTexture = 1,
		currentHealthTexture = 2
	};

	enum MusicMapNumbers
	{
		anxietyMusic = 0,
	};

	float gameWidth, gameHeight;
};


#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

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
	GameObject* player;

	enum ShaderMapNumbers
	{
		spriteShader = 0
	};

	enum TextureMapNumbers
	{
		playerTexture = 0
	};

	float gameWidth, gameHeight;
};


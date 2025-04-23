#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Animation.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader shader_, bool spriteFlip_, bool animated_ = false);
	~SpriteRenderer();

	void DrawSprite(unsigned int texture_, vec2 position_, vec2 size_, float rotate_, vec3 color_);
	
	void UpdateAnimation(float deltaTime) { animation.Update(deltaTime); }
	Animation* GetAnimationHandler() { return &animation; }

private:
	Shader spriteShader;
	unsigned int spriteVAO, spriteVBO;

	array<float, 24> vertices;

	enum VertexAttributes
	{
		position = 0,
		textureCoordinate = 1
	};

	bool animated;
	Animation animation;
};
#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Animation.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader shader_, bool hor_flip_ = false, bool vert_flip_ = false, bool animated_ = false);
	~SpriteRenderer();

	void DrawSprite(unsigned int texture_, vec2 position_, vec2 size_, float rotate_, vec3 color_);
	
	void UpdateAnimation(float deltaTime) { animation.Update(deltaTime); }
	Animation* GetAnimationHandler() { return &animation; }

	void SetHorFlip(bool flip) { hor_flip = flip; }
	void SetVertFlip(bool flip) { vert_flip = flip; }

	void ToggleHorFlip() { hor_flip = !hor_flip; }
	void ToggleVertFlip() { vert_flip = !vert_flip; }

	bool GetHorFlip() { return bool(hor_flip); }
	bool GetVertFlip() { return bool(vert_flip); }

private:
	Shader spriteShader;
	unsigned int spriteVAO, spriteVBO;

	array<float, 24> vertices;

	enum VertexAttributes
	{
		position = 0,
		textureCoordinate = 1
	};

	int hor_flip;
	int vert_flip;

	bool animated;
	Animation animation;
};
#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader shader_);
	~SpriteRenderer();

	void DrawSprite(unsigned int texture_, vec2 position_, vec2 size_, float rotate_, vec3 color_);

private:
	Shader spriteShader;
	unsigned int spriteVAO, spriteVBO;

	array<float, 24> vertices;

	enum VertexAttributes
	{
		position = 0,
		textureCoordinate = 1
	};
};
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <glad/glad.h>
#include <glm.hpp>

#include "SpriteRenderer.h"

class UserInterface
{
public:
	vec2 position, size;
	vec3 color;

	unsigned int sprite;

	UserInterface(vec2 pos_, vec2 size_, unsigned int sprite_, vec3 color_);

	virtual void DrawSprite(SpriteRenderer& renderer_);
};

#endif
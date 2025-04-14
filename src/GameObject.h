#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm.hpp>

#include "SpriteRenderer.h"

class GameObject
{
public:
	vec2 position, size, velocity;
	vec3 color;
	float rotation;
	bool destroyed;

	unsigned int sprite;

	GameObject(vec2 pos_, vec2 size_, unsigned int sprite_, vec3 color_, vec2 velocity_);

	virtual void DrawSprite(SpriteRenderer& renderer_);
};

#endif
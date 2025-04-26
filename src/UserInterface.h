#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <glad/glad.h>
#include <glm.hpp>

#include "SpriteRenderer.h"

class UserInterface
{
private:
	static SpriteRenderer* uiRendererInstance;
public:
	static SpriteRenderer* UiRendererInstance();
	

	vec2 rel_pos, rel_size;
	vec2 position, size;
	vec3 color;

	unsigned int sprite;

	UserInterface(vec2 rel_pos_, vec2 rel_size_, unsigned int sprite_, unsigned int shader_, vec3 color_ = vec3(1.0));
	
	virtual void Update(bool keep_abs = false);
	virtual void Draw(SpriteRenderer& renderer_);
};

#endif
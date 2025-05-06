#ifndef USERINTERFACE_H
#define USERINTERFACE_H

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

	UserInterface(vec2 pos_, vec2 size_, unsigned int sprite_, unsigned int shader_, vec3 color_ = vec3(1.0), bool abs_game_ = false);
	
	virtual void Update(bool keep_abs = false);
	virtual void Draw(SpriteRenderer& renderer_, vec2 rel_offset_ = vec2(0.0), bool relative_to_game = false);
};

#endif
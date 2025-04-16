#include "UserInterface.h"

UserInterface::UserInterface(vec2 pos_, vec2 size_, unsigned int sprite_, vec3 color_)
{
	position = pos_;
	size = size_;
	sprite = sprite_;
	color = color_;
}

void UserInterface::DrawSprite(SpriteRenderer& renderer_)
{
	renderer_.DrawSprite(sprite, position, size, 0.0f, color);
}
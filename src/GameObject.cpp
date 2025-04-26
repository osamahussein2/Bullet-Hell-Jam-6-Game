#include "GameObject.h"
#include "ResourceManager.h"

GameObject::GameObject(vec2 pos_, vec2 size_, unsigned int sprite_, vec3 color_, vec2 velocity_)
{
	position = pos_;
	size = size_;
	sprite = ResourceManager::GetTexture(sprite_);
	color = color_;
	velocity = velocity_;

	rotation = 0.0f;
	destroyed = false;
}

void GameObject::DrawSprite(SpriteRenderer& renderer_)
{
	renderer_.DrawSprite(sprite, position, size, rotation, color);
}

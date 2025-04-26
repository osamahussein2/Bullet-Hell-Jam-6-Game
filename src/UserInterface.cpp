#include "UserInterface.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Assets.h"

SpriteRenderer *UserInterface::uiRendererInstance = nullptr;

SpriteRenderer *UserInterface::UiRendererInstance()
{
	if (uiRendererInstance == nullptr)
	{
		uiRendererInstance = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, false);
	}
  
	return uiRendererInstance;
}

UserInterface::UserInterface(vec2 rel_pos_, vec2 rel_size_, unsigned int sprite_, unsigned int shader_, vec3 color_)
{
	rel_pos = rel_pos_;
	rel_size = rel_size_;
	sprite = ResourceManager::GetTexture(sprite_);
	color = color_;
}

void UserInterface::Update(bool keep_abs)
{
	if (keep_abs){
		position = rel_pos * Window::Instance()->GetGameSize();
		size = rel_size * Window::Instance()->GetGameSize();
	}
	else {
		position = rel_pos * Window::Instance()->GetWindowSize();
		size = rel_size * Window::Instance()->GetWindowSize();
	}
}

void UserInterface::Draw(SpriteRenderer& renderer_)
{
	renderer_.DrawSprite(sprite, position, size, 0.0f, color);
}
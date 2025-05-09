#include "UserInterface.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Assets.h"
#include "Game.h"

SpriteRenderer *UserInterface::uiRendererInstance = nullptr;

SpriteRenderer *UserInterface::UiRendererInstance()
{
	if (uiRendererInstance == nullptr)
	{
		uiRendererInstance = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, false);
	}
  
	return uiRendererInstance;
}

UserInterface::UserInterface(vec2 pos_, vec2 size_, unsigned int sprite_, unsigned int shader_, vec3 color_, bool abs_game_)
{
	if (abs_game_) { // pos_ and size_ aren't relative here, so we convert them to be relative
		vec2 gSize = Window::Instance()->GetGameSize();
		vec2 aSize = Game::Instance()->ArenaSize();
		position = pos_ * aSize / gSize;
		size = size_ * aSize / gSize;
	}
	else {
		rel_pos = pos_;
		rel_size = size_;
	}
	sprite = ResourceManager::GetTexture(sprite_);
	color = color_;
}

void UserInterface::Update(bool relative_to_game)
{
	if (!relative_to_game) {
		position = rel_pos * Window::Instance()->GetWindowSize();
		size = rel_size * Window::Instance()->GetWindowSize();
	}
}

void UserInterface::Draw(SpriteRenderer& renderer_, vec2 rel_offset_, bool relative_to_game)
{
	if (relative_to_game) {
		renderer_.DrawSprite(sprite, position+rel_offset_*Game::Instance()->ArenaSize(), size, 0.0f, color);
	}
	else {
		renderer_.DrawSprite(sprite, position+rel_offset_* Window::Instance()->GetWindowSize(), size, 0.0f, color);
	}
	
}
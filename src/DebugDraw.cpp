#include "DebugDraw.h"
#include "Input.h"

Debug *Debug::DebugInstance = nullptr;

bool Debug::debugCollisions = false;
bool Debug::debugSprite = false;

Debug *Debug::Instance()
{
	if (DebugInstance == nullptr)
	{
		DebugInstance = new Debug();
	}
	return DebugInstance;
}

void Debug::DrawCircle(vec2 pos_, float rad_)
{
    DrawSprite(ResourceManager::GetTexture(Assets::circleTexture), pos_, vec2(2*rad_), 0.f, vec3(1.0));
}

void Debug::DrawRectangle(vec2 pos_, vec2 size_)
{
    DrawSprite(ResourceManager::GetTexture(Assets::rectangleTexture), pos_, size_, 0.f, vec3(1.0));
}

void Debug::Update() {
    if (Input::IsKeyPressed(GLFW_KEY_1)) {
        debugCollisions = !debugCollisions;
    }
    if (Input::IsKeyPressed(GLFW_KEY_2)) {
        debugSprite = !debugSprite;
    }    
}

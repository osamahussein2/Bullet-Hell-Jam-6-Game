#include "BackgroundRenderer.h"

BackgroundRenderer *BackgroundRenderer::BackgroundRendererInstance = nullptr;

BackgroundRenderer *BackgroundRenderer::Instance()
{
	if (BackgroundRendererInstance == nullptr)
	{
		BackgroundRendererInstance = new BackgroundRenderer();
	}
	return BackgroundRendererInstance;
}

BackgroundRenderer::BackgroundRenderer() :
SpriteRenderer(ResourceManager::GetShader(Assets::backgroundShader), false, false, false)
{
}


void BackgroundRenderer::DrawBackground(glm::vec2 size)
{
    DrawSprite(
        ResourceManager::GetTexture(Assets::rectangleTexture),
        vec2(0.0),
        size,
        0.f,
        vec3(1.0)
    );
    //glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

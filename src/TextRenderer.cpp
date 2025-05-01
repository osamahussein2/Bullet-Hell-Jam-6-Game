#include "TextRenderer.h"

TextRenderer *TextRenderer::TextRendererInstance = nullptr;

TextRenderer *TextRenderer::Instance()
{
	if (TextRendererInstance == nullptr)
	{
		TextRendererInstance = new TextRenderer(ResourceManager::GetTexture(Assets::textAtlas), ResourceManager::GetShader(Assets::spriteShader));
	}
	return TextRendererInstance;
}

void TextRenderer::DrawChar(char letter, float x, float y, float w, float h)
{
    int index = int(letter);
    if (letter == ' ') {
        GetAnimationHandler()->SetFrame(36);
    }
    else if (index >= 97 && index <= 122){
        GetAnimationHandler()->SetFrame(index-97);
    }
    else if (index >= 48 && index <= 57){
        GetAnimationHandler()->SetFrame(index-48+26);
    }
    else if (index >= 33 && index <= 47){
        GetAnimationHandler()->SetFrame(index-33+37);
    }
    DrawSprite(atlas, vec2(x, y), vec2(w, h), 0.f, vec3(1.0, 1.0, 1.0));
}

void TextRenderer::DrawText(const char* text, vec2 pos, float scale)
{
    int l = strlen(text);

    float x = pos.x;
    float y = pos.y;

    float w = letW*scale;
    float h = letH*scale;

    float offset = 1.0*scale;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        DrawChar(text[i], x, y, w, h);
        x += w + offset;
    }
}
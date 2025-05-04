#include "TextRenderer.h"
#include "Window.h"

TextRenderer *TextRenderer::TextRendererInstance = nullptr;

TextRenderer *TextRenderer::Instance()
{
	if (TextRendererInstance == nullptr)
	{
		TextRendererInstance = new TextRenderer(ResourceManager::GetTexture(Assets::textAtlas), ResourceManager::GetShader(Assets::spriteShader));
	}
	return TextRendererInstance;
}

void TextRenderer::DrawChar(char letter, float x, float y, float w, float h, vec3 color)
{
    int index = int(letter);
    if (letter == ' ') {
        GetAnimationHandler()->SetFrame(36);
    }
    else if (index >= 97 && index <= 122){ // abcefgh...
        GetAnimationHandler()->SetFrame(index-97);
    }
    else if (index >= 48 && index <= 57){ // 0123456789
        GetAnimationHandler()->SetFrame(index-48+26);
    }
    else if (index >= 33 && index <= 47){ // some special characters (but not all of them)
        GetAnimationHandler()->SetFrame(index-33+37);
    }
    else if (index == 63){ // question mark, special case for now
        GetAnimationHandler()->SetFrame(52);
    }
    DrawSprite(atlas, vec2(x, y), vec2(w, h), 0.f, color);
}

void TextRenderer::DrawText(const char* text, vec2 pos, float scale, bool centered_h, bool centered_v, vec3 color)
{
    float w = letW*scale;
    float h = letH*scale;

    float x = pos.x;
    float y = pos.y;

    float offset = 0.0*scale;

    if (centered_h){
        int l = strlen(text);
        x -= l*w/2;
        x -= l*offset/2;
    }
    if (centered_v){
        y -= h/2;
    }
    
    for (int i = 0; text[i] != '\0'; ++i) {
        DrawChar(text[i], x, y, w, h, color);
        x += w + offset;
    }
}

void TextRenderer::DrawTextFromRight(const char *text, vec2 pos, float scale, bool centered_v, vec3 color)
{
    float w = letW*scale;
    float h = letH*scale;

    float x = pos.x;
    float y = pos.y;

    float offset = 0.0*scale;

    if (centered_v){
        y -= h/2;
    }
    
    int l = strlen(text);
    for (int i = l-1; i>=0; --i) {
        DrawChar(text[i], x, y, w, h, color);
        x -= w + offset;
    }
}

void TextRenderer::DrawTextRelCent(const char *text, vec2 rel_pos, float rel_scale, vec3 color)
{
    DrawText(text, rel_pos*Window::Instance()->GetWindowSize(), rel_scale*Window::Instance()->GetWindowSize().x, true, true, color);
}

void TextRenderer::DrawTextRelFromRight(const char *text, vec2 rel_pos, float rel_scale, vec3 color)
{
    DrawTextFromRight(text, rel_pos*Window::Instance()->GetWindowSize(), rel_scale*Window::Instance()->GetWindowSize().x, true, color);
}
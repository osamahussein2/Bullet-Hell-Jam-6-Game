#include "Beholder.h"
#include "Window.h"
#include "Game.h"

void Beholder::OnCollide(Body *other)
{
}

Beholder::Beholder(vec2 pos_) : Enemy(pos_, vec2(224, 136), Assets::beholderTexture, 1.2, 1.0) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 1;
    const int rows = 1;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BH_IDLE, 4, 6.f});

    collisions.push_back(new CircleCollision(16, size*0.5f));

    float w = Window::Instance()->GetGameSize().x;
    phase = std::asin( (position.x+size.x/2 - w/2)/amplitude/w );
}

void Beholder::Update(float deltaTime)
{
    Window* win = Window::Instance();
    Game* game = Game::Instance();

    if (position.y < win->GetGameSize().y/5) {
        velocity.y = 40;
    }
    else velocity.y = 0;

    position += velocity*deltaTime;
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void Beholder::UpdateCurrentAnim()
{
}

void Beholder::Move(float deltaTime)
{
}

void Beholder::Shoot()
{
}

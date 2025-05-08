#include "Bullet.h"
#include "Game.h"
#include "Enemy.h"

void PlayerBullet::OnCollide(Body *other)
{
    StraightBullet::OnCollide(other);
    if (dynamic_cast<Enemy*>(other)) {
        Game::Instance()->playerAura += 0.015;    
    }
}

PlayerBullet::PlayerBullet(vec2 pos_, vec2 direction_) : StraightBullet(pos_, direction_, Assets::playerBulletTexture)
{
    damage = 0.1;
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 1;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, 0, 6, 6.f});

    collisions.push_back(new CircleCollision(radius, size*0.5f));

    Game::Instance()->playerAura -= 0.01;
}
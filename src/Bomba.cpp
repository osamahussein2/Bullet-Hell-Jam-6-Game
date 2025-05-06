#include "Bomba.h"

Bomba::Bomba(vec2 pos_) : Enemy(pos_, vec2(64, 64), Assets::bombaTexture, 0.2, 1.0) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 1;
    const int rows = 2;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_IDLE, 1, 50.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_ACTIVE, 1, 50.f});

    collisions.push_back(new CircleCollision(16, size*0.5f));
}
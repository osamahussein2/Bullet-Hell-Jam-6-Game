#ifndef BOMBA_H
#define BOMBA_H

#include "Enemy.h"
#include "Assets.h"

enum BombaAnimations {
    BM_IDLE = 0,
    BM_ACTIVE = 1
};

class Bomba : public Enemy {
public:
    virtual void OnCollide(Body* other) override {
        renderer->GetAnimationHandler()->SetCurrentAnim(BM_ACTIVE);
        renderer->GetAnimationHandler()->SetFrameCount(0);
        renderer->GetAnimationHandler()->QueueAnim(BM_IDLE);
    };

    Bomba(vec2 pos_) : Enemy(pos_, vec2(64, 64), Assets::bombaTexture, 0.2) {
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 1;
        const int rows = 2;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_IDLE, 1, 50.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_ACTIVE, 1, 50.f});

        collisions.push_back(new CircleCollision(16, vec2(20.0)));
    }

    virtual void Update(float deltaTime) override {
        GameObjectPro::Update(deltaTime);
        
    };
    virtual void UpdateCurrentAnim() override {};
};

#endif
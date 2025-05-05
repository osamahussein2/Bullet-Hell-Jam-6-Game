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

    Bomba(vec2 pos_);

    virtual void Update(float deltaTime) override {
        GameObjectPro::Update(deltaTime);
        
    };
    virtual void UpdateCurrentAnim() override {};
};

#endif
#ifndef BOMBA_H
#define BOMBA_H

#include "Enemy.h"
#include "Assets.h"

enum BombaAnimations {
    BM_IDLE = 0,
    BM_ACTIVE = 1
};

enum BombaState {
    BM_ST_IDLE = 0,
    BM_ST_ACTIVE = 1
};

class Bomba : public Enemy {
private:

    BombaState state = BM_ST_IDLE;
    bool hit_this_frame = false;

public:
    virtual void OnCollide(Body* other) override;
    Bomba(vec2 pos_);

    virtual void Update(float deltaTime) override;
    
    virtual void UpdateCurrentAnim() override {
        switch (state) {
            case BM_ST_IDLE:
                renderer->GetAnimationHandler()->SetCurrentAnim(BM_IDLE);
                break;
            case BM_ST_ACTIVE:
                renderer->GetAnimationHandler()->SetCurrentAnim(BM_ACTIVE);
                break;
        }
    };
    void Shoot();
};

#endif
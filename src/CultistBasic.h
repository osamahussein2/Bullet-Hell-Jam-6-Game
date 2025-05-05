#ifndef BASIC_CULTIST_H
#define BASIC_CULTIST_H

#include "Enemy.h"
#include "Assets.h"

enum CultistBasicAnimations {
    CLB_HIT = 0,
    CLB_SHOOT = 1,
    CLB_LEFT = 2,
    CLB_RIGHT = 3,
    CLB_IDLE = 4
};

enum CultistBasicState {
    CLB_ST_HIT = 0,
    CLB_ST_SHOOT = 1,
    CLB_ST_MOVE = 2,
    CLB_ST_IDLE = 3
};

class CultistBasic : public Enemy {
private:
    CultistBasicState state = CLB_ST_MOVE;
    bool hit_this_frame = false;
    float moving_timer = 0.f;
    float random_shoot_offset = 0.f; // randomizes shoot cooldown a little

    // movement pattern
    float frequency = 1.f;
    float amplitude = 0.4; // relative to the arena size
    float phase;

public:
    virtual void OnCollide(Body* other);

    CultistBasic(vec2 pos_);

    virtual void Update(float deltaTime) override;

    virtual void UpdateCurrentAnim() override;
};

#endif
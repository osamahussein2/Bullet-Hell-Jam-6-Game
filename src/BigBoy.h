#ifndef BIG_BOY_H
#define BIG_BOY_H

#include "Enemy.h"
#include "Assets.h"

enum BigBoyAnimations {
    BB_HIT = 0,
    BB_RLEG = 1,
    BB_LLEG = 2,
    BB_IDLE = 3
};

enum BigBoyState {
    BB_ST_HIT = 0,
    BB_ST_MOVE = 1,
    BB_ST_DEAD = 2
};

class BigBoy : public Enemy {
private:
    BigBoyState state = BB_ST_MOVE;
    bool hit_this_frame = false;
    float moving_timer = 0.f;
    float random_shoot_offset = 0.f; // randomizes shoot cooldown a little
    float time_dead = 0.f;

    float since_step_shot = 0.f;
    float step_shoot_cooldown = 0.2f;

    // movement pattern
    float frequency = 1.f;
    float amplitude = 0.3; // relative to the arena size
    float phase;

    bool right_step = true;

public:
    virtual void OnCollide(Body* other);

    BigBoy(vec2 pos_);

    virtual void Update(float deltaTime) override;

    virtual void UpdateCurrentAnim() override;

    void Move(float deltaTime);
    void ShootStep();
    void Shoot();

    virtual void Draw();
};

#endif
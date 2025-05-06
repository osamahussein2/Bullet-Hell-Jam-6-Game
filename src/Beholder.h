#ifndef BEHOLDER_H
#define BEHOLDER_H

#include "Enemy.h"
#include "Assets.h"

enum BeholderAnimations {
    BH_IDLE = 0,
};

enum BeholderState {
    BH_ST_IDLE = 0
};

class Beholder : public Enemy {
private:
    BeholderState state = BH_ST_IDLE;
    bool hit_this_frame = false;
    float moving_timer = 0.f;
    float random_shoot_offset = 0.f; // randomizes shoot cooldown a little
    float time_dead = 0.f;

    // movement pattern
    float frequency = 1.f;
    float amplitude = 0.4; // relative to the arena size
    float phase;

public:
    virtual void OnCollide(Body* other);

    Beholder(vec2 pos_);

    virtual void Update(float deltaTime) override;

    virtual void UpdateCurrentAnim() override;

    void Move(float deltaTime);
    void Shoot();

    virtual void Draw() {
        ShootingObject::Draw();
    }
};

#endif
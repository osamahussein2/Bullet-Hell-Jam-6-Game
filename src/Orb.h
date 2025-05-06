#ifndef ORB_H
#define ORB_H

#include "Enemy.h"
#include "Assets.h"

enum OrbAnimations {
    ORB_HIT = 0,
    ORB_IDLE = 1
};

enum OrbState {
    ORB_ST_HIT = 0,
    ORB_ST_MOVE = 1,
    ORB_ST_SHOOT = 2,
    ORB_ST_DEAD = 3,
};

class Orb : public Enemy {
private:
    OrbState state = ORB_ST_MOVE;
    bool hit_this_frame = false;
    float time_dead = 0.f;
    float random_shoot_offset = 0.f; // randomizes shoot cooldown a little
    float moving_timer = 0.f;
public:
    virtual void OnCollide(Body* other) override;

    Orb(vec2 pos_);

    virtual void Update(float deltaTime) override;
    virtual void UpdateCurrentAnim() override;
    void Move(float deltaTime);
};

#endif
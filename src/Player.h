#ifndef PLAYER_H
#define PLAYER_H

#include "ShootingObject.h"
#include "Assets.h"

// match y_pos (from 0) in spritesheet
enum PlayerAnimations {
    PL_IDLE = 0, 
    PL_RIGHT = 1,
    PL_LEFT = 2,
    PL_SPIN = 3,
    PL_SHOOT = 4,
    PL_HIT = 5
};

enum PlayerState {
    PL_ST_IDLE = 0, 
    PL_ST_MOVE = 1,
    PL_ST_HIT = 2,
    PL_ST_SHOOT = 3,
    PL_ST_DEAD = 4
};

class Player : public ShootingObject {
private:
    PlayerState state = PL_ST_IDLE;
    bool hit_this_frame = false;
    float acceleration = 2000.f;
    float drag = 8;
    bool low_on_aura = false;
    float time_dead = 0.f;

public:
    virtual void OnCollide(Body* other);

    Player(vec2 pos_);

    virtual void Update(float deltaTime) override;
    virtual void UpdateCurrentAnim() override;

    vec2 HandleMovementInput();
    bool CanShoot();
    void Shoot();

    virtual void Die() override;

    float GetTimeDead() { return time_dead; }
};

#endif
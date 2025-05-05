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
};

enum PlayerState {
    PL_ST_IDLE = 0, 
    PL_ST_MOVE = 1,
    PL_ST_HIT = 2,
    PL_ST_SHOOT = 3
};

class Player : public ShootingObject {
private:
    PlayerState state = PL_ST_IDLE;
    bool hit_this_frame = false;
    float speed = 2000.f;
    float acceleration = 0.0f;
    float maxAccelerationTime = 3.0f;
    float maxDecelerationTime = 1.0f;

    bool shouldPlayerAccelerate = false;

public:
    virtual void OnCollide(Body* other);

    Player(vec2 pos_);

    virtual void Update(float deltaTime) override;
    virtual void UpdateCurrentAnim() override;

    vec2 HandleMovementInput();
    void Shoot();
};

#endif
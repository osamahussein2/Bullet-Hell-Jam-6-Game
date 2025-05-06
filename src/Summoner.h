#ifndef SUMMONER_H
#define SUMMONER_H

#include "Enemy.h"
#include "Assets.h"

enum SummonerAnimations {
    CLB_HIT = 0,
    CLB_SHOOT = 1,
    CLB_LEFT = 2,
    CLB_RIGHT = 3,
    CLB_IDLE = 4
};

enum SummonerState {
    CLB_ST_HIT = 0,
    CLB_ST_SHOOT = 1,
    CLB_ST_MOVE = 2,
    CLB_ST_IDLE = 3
};

class Summoner : public Enemy {
private:
    SummonerState state = CLB_ST_MOVE;
    bool hit_this_frame = false;
    float moving_timer = 0.f;
    float random_shoot_offset = 0.f; // randomizes shoot cooldown a little

    // movement pattern
    float frequency = 1.f;
    float amplitude = 0.4; // relative to the arena size
    float phase;

public:
    virtual void OnCollide(Body* other);

    Summoner(vec2 pos_);

    virtual void Update(float deltaTime) override;

    virtual void UpdateCurrentAnim() override;
};

#endif
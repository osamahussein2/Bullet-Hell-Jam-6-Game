#ifndef SUMMONER_H
#define SUMMONER_H

#include "Enemy.h"
#include "Assets.h"

enum SummonerAnimations {
    SM_HIT = 0,
    SM_SUMMON = 1,
    SM_RIGHT = 2,
    SM_LEFT = 3,
    SM_IDLE = 4
};

enum SummonerState {
    SM_ST_HIT = 0,
    SM_ST_SUMMON = 1,
    SM_ST_MOVE = 2,
    SM_ST_IDLE = 3
};

class Summoner : public Enemy {
private:
    SummonerState state = SM_ST_MOVE;
    bool hit_this_frame = false;
    float moving_timer = 0.f;
    float random_shoot_offset = -3.f; // randomizes shoot cooldown a little

    // movement pattern
    float frequency = 0.5f;
    float amplitude = 0.45; // relative to the arena size
    float phase;

public:
    virtual void OnCollide(Body* other);

    Summoner(vec2 pos_);

    virtual void Update(float deltaTime) override;

    virtual void UpdateCurrentAnim() override;
};

#endif
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
    ORB_ST_IDLE = 1,
};

class Orb : public Enemy {
private:
    OrbState state = ORB_ST_IDLE;
    bool hit_this_frame = false;

public:
    virtual void OnCollide(Body* other) override;

    Orb(vec2 pos_);

    virtual void Update(float deltaTime) override;
    virtual void UpdateCurrentAnim() override;
};

#endif
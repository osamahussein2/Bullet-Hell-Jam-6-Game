#ifndef ENEMY_H
#define ENEMY_H

#include "ShootingObject.h"

class Enemy : public ShootingObject {

public:

    Enemy(vec2 pos_, vec2 size_, unsigned sprite, float cooldown_) : ShootingObject(pos_, size_, sprite, cooldown_) {
    }
    
};

#endif
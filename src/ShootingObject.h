#ifndef SHOOTING_OBJECT_H
#define SHOOTING_OBJECT_H

#include "GameObjectPro.h"

class ShootingObject : public GameObjectPro {
protected:    
    float shoot_cooldown;
    float since_last_shot; // already can shoot
public:
    ShootingObject(vec2 pos_, vec2 size_, unsigned sprite_, float shoot_cooldown_, bool ready_to_shoot_ = true) : 
    shoot_cooldown(shoot_cooldown_), since_last_shot(0.f), GameObjectPro(pos_, size_, sprite_) {
        if (ready_to_shoot_) {
            since_last_shot = shoot_cooldown + 1;
        }
    }

    virtual void Die();
};

#endif
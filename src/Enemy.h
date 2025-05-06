#ifndef ENEMY_H
#define ENEMY_H

#include "ShootingObject.h"
#include "UserInterface.h"

class Enemy : public ShootingObject {

protected:
    float max_health;
    float health;

public:

    Enemy(vec2 pos_, vec2 size_, unsigned sprite, float cooldown_, float health_) : health(health_), max_health(health_), ShootingObject(pos_, size_, sprite, cooldown_) {
    }
    
    virtual void Draw() {
        ShootingObject::Draw();
        UserInterface::UiRendererInstance()->DrawSprite(
            ResourceManager::GetTexture(Assets::enemyHealthTexture), position+vec2(0, -10),
            vec2(size.x, 3), 
            0, vec3(0.5)
        );
        UserInterface::UiRendererInstance()->DrawSprite(
            ResourceManager::GetTexture(Assets::enemyHealthTexture), position+vec2(0, -10),
            vec2(size.x*health/max_health, 3), 
            0, vec3(1.0)
        );
    }
};

#endif
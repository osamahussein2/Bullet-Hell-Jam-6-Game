#ifndef ENEMY_H
#define ENEMY_H

#include "ShootingObject.h"
#include "UserInterface.h"

class Enemy : public ShootingObject {

protected:
    float max_health;
    float health;

    vec2 spawn_pos;
    bool reached_spawn = false;

public:

    Enemy(vec2 pos_, vec2 size_, unsigned sprite, float cooldown_, float health_, bool in_spawn_ = false) : spawn_pos(pos_), health(health_), max_health(health_), ShootingObject(vec2(pos_.x, -10), size_, sprite, cooldown_) {
        if (in_spawn_) {
            position = pos_-size*0.5f;
            reached_spawn = true;
        }
    }
    
    bool ReachedSpawn() {
        if (reached_spawn) return true;
        vec2 d = spawn_pos-position-size*0.5f;
        if (length(d) <= 3) {
            reached_spawn = true;
            velocity = vec2(0.0);
            return true;
        }
        
        vec2 dir = d;
        if (dir != vec2(0.0)) dir = normalize(dir);

        velocity = 3.f*dir*std::max(length(d), 50.f);
        return false;
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

    void Die();
};

#endif
#ifndef BULLET_H
#define BULLET_H

#include "GameObjectPro.h"
#include "Assets.h"

class Bullet : public GameObjectPro {

protected:
    vec2 direction;
    float speed;
    float radius;

public:
    Bullet(vec2 pos_, vec2 direction_, float speed_, float radius_, vec2 size_, unsigned int sprite_) : 
    direction(direction_), speed(speed_), radius(radius_), GameObjectPro(pos_, size_, sprite_) {}

    virtual void OnCollide(Body& other) override {};
    virtual void UpdateCurrentAnim() override {};
};

class PlayerBullet : public Bullet {
public:
    PlayerBullet(vec2 pos_, vec2 direction_) : Bullet(pos_, direction_, 300.f, 16.f, vec2(32.0), Assets::playerBulletTexture) {
        position -= vec2(radius, radius);
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 6;
        const int rows = 1;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, 0, 6, 6.f});
    }

    virtual void Update(float deltaTime) override {

        velocity = direction * speed;
        position += velocity * deltaTime;

        renderer->UpdateAnimation(deltaTime);
    }
};

#endif
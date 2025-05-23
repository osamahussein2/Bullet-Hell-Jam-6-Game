#ifndef BULLET_H
#define BULLET_H

#include "GameObjectPro.h"
#include "Assets.h"

class Bullet : public GameObjectPro {

protected:
    vec2 initialPosition;
    vec2 initialDirection;
    float initialSpeed;

    vec2 direction;
    float speed;
    float radius;

    float timer = 0.f;

    float damage = 0.13; // full health of a regular unit is 1.0

public:
    Bullet(vec2 pos_, vec2 direction_, float speed_, float radius_, vec2 size_, unsigned int sprite_) : 
    direction(direction_), speed(speed_), radius(radius_), GameObjectPro(pos_, size_, sprite_) {
        initialPosition = position;
        initialDirection = direction;
        initialSpeed = speed;
    }

    virtual void Update(float deltaTime) override {
        timer += deltaTime;
        position += velocity * deltaTime;

        GameObjectPro::Update(deltaTime);

        if (timer > 4) {
            destroyed = true;
        }
    }

    virtual void OnCollide(Body* other) override {
        ResourceManager::GetSound(Assets::hitSound)->Play();
        destroyed = true;
    };
    virtual void UpdateCurrentAnim() override {};

    float GetDamage() { return damage; }
};

class StraightBullet : public Bullet {
public:
    StraightBullet(vec2 pos_, vec2 direction_, unsigned sprite) : Bullet(pos_, direction_, 200.f, 9.f, vec2(32.0), sprite) {
    }

    virtual void Update(float deltaTime) override {
        velocity = direction * speed;
        // custom logic before parent update
        Bullet::Update(deltaTime);
    }
};

class PlayerBullet : public StraightBullet {
public:
    virtual void OnCollide(Body* other) override;
    PlayerBullet(vec2 pos_, vec2 direction_);
};

class StraightEnemyBullet : public StraightBullet {
    public:
        StraightEnemyBullet(vec2 pos_, vec2 direction_) : StraightBullet(pos_, direction_, Assets::enemyBulletTexture) {
            renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
            const int columns = 6;
            const int rows = 1;
    
            renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, 0, 6, 6.f});
    
            collisions.push_back(new CircleCollision(radius, size*0.5f));
        }
    };

class CirlcePatternBullet : public Bullet {
private:
    float angle;
    float angularSpeed = 1;
    float patternRadius;
    float centerSpeed = 120;

public:
    CirlcePatternBullet(vec2 pos_, vec2 direction_, unsigned sprite_, float angle_, float patt_rad_) : 
    angle(angle_), patternRadius(patt_rad_),
    Bullet(pos_, direction_, 200.f, 9.f, vec2(32.0), sprite_) {
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 6;
        const int rows = 1;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, 0, 6, 6.f});

        collisions.push_back(new CircleCollision(radius, size*0.5f));
    }

    virtual void Update(float deltaTime) override {

        angle += angularSpeed * deltaTime;
        vec2 tangentialVelocity = patternRadius * angularSpeed * vec2(-sin(angle), cos(angle));
        vec2 centerVelocity = initialDirection * centerSpeed;
        velocity = centerVelocity + tangentialVelocity;

        // Update position using velocity
        Bullet::Update(deltaTime);
    }
};

#endif
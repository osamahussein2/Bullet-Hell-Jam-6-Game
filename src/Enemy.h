#ifndef ENEMY_H
#define ENEMY_H

#include "ShootingObject.h"
#include "Assets.h"

class Enemy : public ShootingObject {

public:

    Enemy(vec2 pos_, vec2 size_, unsigned sprite, float cooldown_) : ShootingObject(pos_, size_, sprite, cooldown_) {
    }
    
};

// Bomba

enum BombaAnimations {
    BM_IDLE = 0,
    BM_ACTIVE = 1
};

class Bomba : public Enemy {
public:
    virtual void OnCollide(Body* other) override {
        renderer->GetAnimationHandler()->SetCurrentAnim(BM_ACTIVE);
        renderer->GetAnimationHandler()->SetFrameCount(0);
        renderer->GetAnimationHandler()->QueueAnim(BM_IDLE);
    };

    Bomba(vec2 pos_) : Enemy(pos_, vec2(64, 64), Assets::bombaTexture, 0.2) {
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 1;
        const int rows = 2;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_IDLE, 1, 50.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_ACTIVE, 1, 50.f});

        collisions.push_back(new CircleCollision(16, vec2(20.0)));
    }

    virtual void Update(float deltaTime) override {
        GameObjectPro::Update(deltaTime);
        
    };
    virtual void UpdateCurrentAnim() override {};
};

// Basic cultist

enum CultistBasicAnimations {
    CLB_HIT = 0,
    CLB_SHOOT = 1,
    CLB_LEFT = 2,
    CLB_RIGHT = 3,
    CLB_IDLE = 4
};

enum CultistBasicState {
    CLB_ST_HIT = 0,
    CLB_ST_SHOOT = 1,
    CLB_ST_MOVE = 2,
    CLB_ST_IDLE = 3
};

class CultistBasic : public Enemy {
private:
    CultistBasicState state = CLB_ST_MOVE;
    bool hit_this_frame = false;

public:
    virtual void OnCollide(Body* other) override {
        hit_this_frame = true;
    };

    CultistBasic(vec2 pos_) : Enemy(pos_, vec2(64, 80), Assets::cultistBasicTexture, 0.2) {
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 6;
        const int rows = 5;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_HIT, 4, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_SHOOT, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_LEFT, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_RIGHT, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_IDLE, 6, 6.f});

        collisions.push_back(new CircleCollision(16, vec2(20.0)));
    }

    virtual void Update(float deltaTime) override {

        if (hit_this_frame) state = CLB_ST_HIT;
        since_last_shot += deltaTime;


        switch (state) {
        case CLB_HIT:
            if (!hit_this_frame) {
                if (renderer->GetAnimationHandler()->GetCurrentAnimationData().current_frame == renderer->GetAnimationHandler()->GetCurrentAnimationData().frames-1) {
                    state = CLB_ST_MOVE;
                }
            }
            break;
        case CLB_ST_MOVE:
            velocity.x = sin(glfwGetTime())*50;

            if (since_last_shot >= shoot_cooldown){
                Game::Instance()->enemyBullets.push_back(new PlayerBullet(position+size*vec2(0.5), vec2(0.0, 1.0)));
                Game::Instance()->enemyBullets.push_back(new PlayerBullet(position+size*vec2(0.5), vec2(cos(M_PI/2+M_PI/7), sin(M_PI/2+M_PI/7))));
                Game::Instance()->enemyBullets.push_back(new PlayerBullet(position+size*vec2(0.5), vec2(cos(M_PI/2-M_PI/7), sin(M_PI/2-M_PI/7))));
                since_last_shot = 0.f;
            }

            break;
        default:
            break;
        }
        position += velocity*deltaTime;
        UpdateCurrentAnim();
        GameObjectPro::Update(deltaTime);
        hit_this_frame = false;
    };
    virtual void UpdateCurrentAnim() override {
        switch (state) {
            case CLB_ST_IDLE:
                renderer->GetAnimationHandler()->SetCurrentAnim(CLB_IDLE);
                break;
            case CLB_ST_HIT:
                renderer->GetAnimationHandler()->SetCurrentAnim(CLB_HIT);
                break;
            case CLB_ST_MOVE:
                if (velocity.x > 0) renderer->GetAnimationHandler()->SetCurrentAnim(CLB_RIGHT);
                else if (velocity.x < 0) renderer->GetAnimationHandler()->SetCurrentAnim(CLB_LEFT);
                break;
        }
    };
};

#endif
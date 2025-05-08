#include "CultistBasic.h"
#include "Game.h"
#include "Bullet.h"

#include <math.h>
#include "Player.h"

#include "Window.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void CultistBasic::OnCollide(Body *other) {
    if (state != CLB_ST_HIT && state != CLB_SHOOT) {
        state = CLB_ST_HIT;
        hit_this_frame = true;
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            health -= bullet->GetDamage();
        }
    }
}
CultistBasic::CultistBasic(vec2 pos_) : Enemy(pos_, vec2(64, 80), Assets::cultistBasicTexture, 0.2, 1.0) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 5;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_HIT, 4, 6.f, false});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_SHOOT, 6, 7.f, false});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_LEFT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_RIGHT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, CLB_IDLE, 6, 6.f});

    collisions.push_back(new CircleCollision(16, size*0.5f));

    float w = Window::Instance()->GetGameSize().x;
    phase = std::asin( (position.x+size.x/2 - w/2)/amplitude/w );
}

void CultistBasic::Update(float deltaTime) {
    since_last_shot += deltaTime;

    if (health <= 0) state = CLB_ST_DEAD;
    switch (state) {
    case CLB_ST_HIT:
        Move(deltaTime);
        if (!hit_this_frame) {
            if (renderer->GetAnimationHandler()->AnimEnded()) {
                state = CLB_ST_MOVE;
                renderer->GetAnimationHandler()->RestartAnim(CLB_HIT);
            }
        }
        break;
    case CLB_ST_MOVE:
        Move(deltaTime);
        if (since_last_shot + random_shoot_offset >= shoot_cooldown) {
            state = CLB_ST_SHOOT;
            random_shoot_offset = -((double)std::rand() / (RAND_MAX))*3;
        }
        break;
    case CLB_ST_SHOOT:
        velocity.x = 0.f;
        if (since_last_shot >= shoot_cooldown){
            Shoot();
        }
        if (renderer->GetAnimationHandler()->AnimEnded()) {
            state = CLB_ST_MOVE;
            renderer->GetAnimationHandler()->RestartAnim(CLB_SHOOT);
        }
        break;
    case CLB_ST_DEAD:
        velocity = vec2(0.0);
        time_dead += deltaTime;
        if (time_dead > 0.f) {
            destroyed = true;
        }
        break;
    }
    position += velocity*deltaTime;
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void CultistBasic::UpdateCurrentAnim() {
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
        case CLB_ST_SHOOT:
            renderer->GetAnimationHandler()->SetCurrentAnim(CLB_SHOOT);
            break;
    }
}
void CultistBasic::Move(float deltaTime) {
    moving_timer += deltaTime;
    float w = Window::Instance()->GetGameSize().x;
    velocity.x = w*amplitude*cos(moving_timer+phase);
}
void CultistBasic::Shoot() {
    int n = 10;
    float a = 2*M_PI / n;
    float patt_rad = 15;
    for (int i = 0; i < n; i++) {
        float ang = i*a;
        vec2 offset = vec2(cos(ang), sin(ang))*patt_rad;
        vec2 dir = Game::Instance()->player->position - position;
        if (dir != vec2(0.0)) dir = normalize(dir);
        Game::Instance()->enemyBullets.push_back(new CirlcePatternBullet(position+size*vec2(0.5)+offset, dir, Assets::enemyBulletTexture, ang, patt_rad));
    }

    since_last_shot = 0.f;
};
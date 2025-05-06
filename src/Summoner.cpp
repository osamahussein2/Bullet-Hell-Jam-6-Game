#include "Summoner.h"
#include "Game.h"
#include "Bullet.h"
#include "Orb.h"
#include "CultistBasic.h"
#include <math.h>

#include "Window.h"

void Summoner::OnCollide(Body *other) {
    if (state != SM_ST_HIT && state != SM_ST_SUMMON) {
        state = SM_ST_HIT;
        hit_this_frame = true;
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            health -= bullet->GetDamage();
        }
    }
}
Summoner::Summoner(vec2 pos_) : Enemy(pos_, vec2(64, 80), Assets::summonerTexture, 1.0, 1.0) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 5;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, SM_HIT, 4, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, SM_SUMMON, 6, 7.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, SM_RIGHT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, SM_LEFT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, SM_IDLE, 6, 6.f});

    renderer->GetAnimationHandler()->SetCurrentAnim(SM_IDLE);

    collisions.push_back(new CircleCollision(16, size*0.5f));

    float w = Window::Instance()->GetGameSize().x;
    phase = std::asin( (position.x+size.x/2 - w/2)/amplitude/w );
}

void Summoner::Update(float deltaTime) {

    since_last_shot += deltaTime;

    if (health <= 0) state = SM_ST_DEAD;
    switch (state) {
    case SM_ST_HIT:
        Move(deltaTime);
        if (renderer->IsLastFrame()) {
            state = SM_ST_MOVE;
        }
    
        break;
    case SM_ST_MOVE:
        Move(deltaTime);
        break;
    case SM_ST_SUMMON:
        velocity.x = 0;
        if (renderer->IsLastFrame()) {
            if (since_last_shot >= shoot_cooldown){
                Game::Instance()->new_enemies.push_back(new Orb(position+size*vec2(0.5)+vec2(0,10)));            
                since_last_shot = 0.f;
            }
            state = SM_ST_MOVE;
        }
        break;
    case SM_ST_DEAD:
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

void Summoner::UpdateCurrentAnim() {
    switch (state) {
        case SM_ST_IDLE:
            renderer->GetAnimationHandler()->SetCurrentAnim(SM_IDLE);
            break;
        case SM_ST_HIT:
            renderer->GetAnimationHandler()->SetCurrentAnim(SM_HIT);
            break;
        case SM_ST_MOVE:
            if (velocity.x > 0) renderer->GetAnimationHandler()->SetCurrentAnim(SM_RIGHT);
            else if (velocity.x < 0) renderer->GetAnimationHandler()->SetCurrentAnim(SM_LEFT);
            else renderer->GetAnimationHandler()->SetCurrentAnim(SM_IDLE);
            break;
        case SM_ST_SUMMON:
            renderer->GetAnimationHandler()->SetCurrentAnim(SM_SUMMON);
            break;
        case SM_ST_DEAD:
            renderer->GetAnimationHandler()->SetCurrentAnim(SM_IDLE);
            break;
    }
}
void Summoner::Move(float deltaTime) {
    moving_timer += deltaTime;
    float w = Window::Instance()->GetGameSize().x;
    velocity.x = w*amplitude*cos(moving_timer+phase);
    if (since_last_shot + random_shoot_offset >= shoot_cooldown) {
        state = SM_ST_SUMMON;
        random_shoot_offset = (((double)std::rand() / (RAND_MAX)) * 2 - 1)*3;
    }
};
#include "Orb.h"
#include "Game.h"
#include "Bullet.h"

void Orb::OnCollide(Body *other)
{
    if (state != ORB_ST_HIT) {
        state = ORB_ST_HIT;
        hit_this_frame = true;
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            health -= bullet->GetDamage();
        }
    }
}

Orb::Orb(vec2 pos_) : Enemy(pos_, vec2(33, 36), Assets::orbTexture, 0.56, 0.4)
{
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 2;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, ORB_HIT, 2, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, ORB_IDLE, 6, 6.f});
    renderer->GetAnimationHandler()->SetCurrentAnim(ORB_IDLE);

    collisions.push_back(new CircleCollision(16, size*0.5f));
}

void Orb::Update(float deltaTime)
{
    since_last_shot += deltaTime;

    if (health <= 0) state = ORB_ST_DEAD;
    switch (state) {
    case ORB_ST_HIT:
        Move(deltaTime);
        if (renderer->IsLastFrame()) {
            state = ORB_ST_MOVE;
        }
        break;
    case ORB_ST_MOVE:
        Move(deltaTime);
        if (since_last_shot + random_shoot_offset >= shoot_cooldown) {
            state = ORB_ST_SHOOT;
            random_shoot_offset = (((double)std::rand() / (RAND_MAX)) * 2 - 1)*0.5;
        }
        break;
    case ORB_ST_SHOOT:
        Move(deltaTime);
        if (since_last_shot >= shoot_cooldown){
            vec2 dir = Game::Instance()->player->position - position;
            if (dir != vec2(0.0)) dir = normalize(dir);
            Game::Instance()->enemyBullets.push_back(new StraightEnemyBullet(position+size*0.5f, dir));
            since_last_shot = 0.f;
        }
        if (renderer->IsLastFrame()) {
            state = ORB_ST_MOVE;
        }
        break;
    case ORB_ST_DEAD:
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

void Orb::UpdateCurrentAnim()
{
    switch (state)
    {
    case ORB_ST_MOVE:
        renderer->GetAnimationHandler()->SetCurrentAnim(ORB_IDLE);
        break;
    case ORB_ST_HIT:
        renderer->GetAnimationHandler()->SetCurrentAnim(ORB_HIT);
        break;
    case ORB_ST_DEAD:
        renderer->GetAnimationHandler()->SetCurrentAnim(ORB_IDLE);
        break;
    }
}

void Orb::Move(float deltaTime)
{    
    moving_timer += deltaTime;
    velocity = vec2(cos(moving_timer), sin(moving_timer))*20.f;
}

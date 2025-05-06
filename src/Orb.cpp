#include "Orb.h"
#include "Game.h"
#include "Bullet.h"

void Orb::OnCollide(Body *other)
{
    hit_this_frame = true;
}

Orb::Orb(vec2 pos_) : Enemy(pos_, vec2(35, 35), Assets::orbTexture, 0.56)
{
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 2;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, ORB_HIT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, ORB_IDLE, 6, 6.f});
    renderer->GetAnimationHandler()->SetCurrentAnim(ORB_IDLE);

    collisions.push_back(new CircleCollision(16, size*0.5f));
}

void Orb::Update(float deltaTime)
{
    if (hit_this_frame) state = ORB_ST_HIT;
    since_last_shot += deltaTime;

    if (since_last_shot >= shoot_cooldown){
        int n = 2;
        float a = 2*M_PI / n;
        float patt_rad = 20;
        for (int i = 0; i < n; i++) {
            float ang = i*a;
            vec2 offset = vec2(cos(ang), sin(ang))*patt_rad;
            vec2 dir = Game::Instance()->player->position - position;
            if (dir != vec2(0.0)) dir = normalize(dir);
            Game::Instance()->enemyBullets.push_back(new CirlcePatternBullet(position+size*vec2(0.5)+offset, dir, Assets::enemyBulletTexture, ang, patt_rad));
        }
    
        since_last_shot = 0.f;
    }
    
    float time = glfwGetTime();
    velocity = vec2(cos(time), sin(time))*20.f;

    position += velocity*deltaTime;
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void Orb::UpdateCurrentAnim()
{
}

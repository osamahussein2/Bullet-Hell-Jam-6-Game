#include "Bomba.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Bomba::OnCollide(Body *other) {
    if (state != BM_ST_ACTIVE) {
        if (Player* player = dynamic_cast<Player*>(other)) {
            Shoot();
            state = BM_ST_ACTIVE;
        }
        else if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            state = BM_ST_ACTIVE;
            health -= bullet->GetDamage();
            hit_this_frame = true;
        }
    }
};

Bomba::Bomba(vec2 pos_) : Enemy(pos_, vec2(64, 64), Assets::bombaTexture, 0.2, 1.0)
{
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 1;
    const int rows = 2;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_IDLE, 1, 1.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BM_ACTIVE, 1, 1.f, false});

    collisions.push_back(new CircleCollision(19, size*0.5f));
}

void Bomba::Update(float deltaTime) {

    Game* game = Game::Instance();
    if (ReachedSpawn()) {
        if (health <= 0) Die();

        switch (state) {
            case BM_ST_IDLE:
                {
                    vec2 dir = game->player->position+game->player->size*0.5f - position - size*0.5f;
                    if (dir != vec2(0.0)) dir = normalize(dir);
                    velocity = dir*32.f;
                }
                break;
            case BM_ST_ACTIVE:
                if (renderer->GetAnimationHandler()->AnimEnded()) {
                    state = BM_ST_IDLE;
                    renderer->GetAnimationHandler()->RestartAnim(BM_ACTIVE);
                }
                break;
        }
    }

    position += velocity*deltaTime;
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void Bomba::Shoot()
{
    int n = 16;
    float ang_off = 2*M_PI/n;
    for (int i = 0; i < n; i++) {
        vec2 dir = vec2(cos(ang_off*i), sin(ang_off*i));
        vec2 pos = position+size*0.5f - 70.f*dir;

        Game::Instance()->enemyBullets.push_back(
            new StraightEnemyBullet(pos, dir)
        );
    }
}

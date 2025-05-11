#include "BigBoy.h"
#include "Game.h"
#include "Bullet.h"
#include "Effect.h"
#include "TextRenderer.h"

void BigBoy::OnCollide(Body *other)
{
    if (state != BB_ST_HIT) {
        if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
            health -= bullet->GetDamage();
            state = BB_ST_HIT;
            hit_this_frame = true;
        }
    }
}

BigBoy::BigBoy(vec2 pos_) : Enemy(pos_, vec2(112, 176), Assets::bigBoyTexture,  0.06, 7.f, true) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 4;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BB_HIT, 2, 6.f, false});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BB_RLEG, 6, 7.f, false});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BB_LLEG, 6, 7.f, false});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BB_IDLE, 6, 6.f});

    renderer->GetAnimationHandler()->SetCurrentAnim(BB_RLEG);

    collisions.push_back(new CircleCollision(16, size*vec2(0.5, 0.4)));

    float w = Game::Instance()->ArenaSize().x;
    phase = std::asin( (position.x+size.x/2 - w/2)/amplitude/w );
}

void BigBoy::Update(float deltaTime)
{
    since_last_shot += deltaTime;
    since_step_shot += deltaTime;
    
    Window* win = Window::Instance();
    Game* game = Game::Instance();

    if (position.y < win->GetGameSize().y/5*1.5) {
        
        int frame = renderer->GetAnimationHandler()->GetFrame();
        if (frame <= 3) velocity.y = 40;
        else velocity.y = 0;
        if (frame == 3 && since_step_shot >= step_shoot_cooldown) {
            ShootStep();
            since_step_shot = 0.f;
        }
        if (renderer->GetAnimationHandler()->AnimEnded()) {
            if (right_step)  {
                renderer->GetAnimationHandler()->RestartAnim(BB_RLEG);
                renderer->GetAnimationHandler()->SetCurrentAnim(BB_LLEG);
                right_step = false;
            }
            else {
                renderer->GetAnimationHandler()->RestartAnim(BB_LLEG);
                renderer->GetAnimationHandler()->SetCurrentAnim(BB_RLEG);
                right_step = true;
            }
        }
    }
    else {
        velocity.y = 0.f;
        if (since_last_shot >= shoot_cooldown) Shoot();
        if (health <= 0) state = BB_ST_DEAD;
        switch (state) {
            case BB_ST_MOVE:
                Move(deltaTime);
                if (renderer->GetAnimationHandler()->GetFrame() == 3 && since_step_shot >= step_shoot_cooldown) {
                    ShootStep();
                    since_step_shot = 0.f;
                }
                if (renderer->GetAnimationHandler()->AnimEnded()) {
                    if (right_step)  {
                        renderer->GetAnimationHandler()->RestartAnim(BB_RLEG);
                        renderer->GetAnimationHandler()->SetCurrentAnim(BB_LLEG);
                        right_step = false;
                    }
                    else {
                        renderer->GetAnimationHandler()->RestartAnim(BB_LLEG);
                        renderer->GetAnimationHandler()->SetCurrentAnim(BB_RLEG);
                        right_step = true;
                    }
                }
                break;
            case BB_ST_HIT:
                Move(deltaTime);
                if (!hit_this_frame) {
                    if (renderer->GetAnimationHandler()->AnimEnded()) {
                        state = BB_ST_MOVE;
                        renderer->GetAnimationHandler()->RestartAnim(BB_HIT);
                    }
                }
                else {
                    renderer->GetAnimationHandler()->SetCurrentAnim(BB_HIT);
                }
                break;
            case BB_ST_DEAD:
                Die();
                break;
        }
    }

    position += velocity*deltaTime;
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void BigBoy::UpdateCurrentAnim()
{    
}

void BigBoy::Move(float deltaTime)
{
    moving_timer += deltaTime;
    float w = Window::Instance()->GetGameSize().x;
    velocity.x = w*amplitude*cos( (moving_timer+phase)/0.3 )*0.3;
}

void BigBoy::ShootStep()
{
    Game* game = Game::Instance(); 
    int n = 6;
    vec2 pos = position+size*vec2(
        (!right_step) ? 0.3 : 0.7,
        0.9
    );
    game->effects.push_back( new Explosion(0.f, pos) );

    for (int i = 0; i < n; i++) {
        float ang_off = M_PI*2.f/n*i;
        vec2 dir = Game::Instance()->player->position - position;
        game->enemyBullets.push_back(new StraightEnemyBullet(pos, vec2(cosf(ang_off), sinf(ang_off))));   
    }
}

void BigBoy::Shoot()
{
    Game* game = Game::Instance();
    float time = glfwGetTime();
    int n = 1;
    if (int(time*3)%4 == 3) {
        for (int i = 0; i < n; i++) {
            //float ang_off = M_PI*2.f/n*i;
            //game->enemyBullets.push_back(new StraightEnemyBullet(position+size*0.5f+vec2(0, -size.y/3), vec2(cosf(time+ang_off), sinf(time+ang_off))));
            vec2 spawn_pos = position+size*0.5f+vec2(0, -size.y/3);
            vec2 dir = game->player->position+game->player->size*0.5f - spawn_pos;
            if (dir != vec2(0.0)) dir = normalize(dir);
            ResourceManager::GetSound(Assets::LaserShootSound)->Play();
            game->enemyBullets.push_back(new StraightEnemyBullet(spawn_pos, dir)); 
        }
    }
    since_last_shot = 0.f;
}


void BigBoy::Draw() {

    Enemy::Draw();
    TextRenderer::Instance()->DrawText(
        "titan", position+size*vec2(0.5, 0)+vec2(0, -13), 0.5, true, true, vec3(1.0)
    );
}
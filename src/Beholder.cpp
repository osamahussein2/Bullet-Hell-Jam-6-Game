#include "Beholder.h"
#include "Window.h"
#include "Bullet.h"
#include "Game.h"
#include "DebugDraw.h"
#include "TextRenderer.h"

void Beholder::OnCollide(Body *other)
{    
    hit_this_frame = true;
    if (Bullet* bullet = dynamic_cast<Bullet*>(other)) {
        health -= bullet->GetDamage();
    }
}

Beholder::Beholder(vec2 pos_) : Enemy(pos_, vec2(232, 168), Assets::beholderTexture, 0.04, 30.f, true) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 1;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, BH_IDLE, 6, 6.f});

    collisions.push_back(new CircleCollision(16, size*0.5f));

    float w = Window::Instance()->GetGameSize().x;
    phase = std::asin( (position.x+size.x/2 - w/2)/amplitude/w );
}

void Beholder::Update(float deltaTime)
{
    Window* win = Window::Instance();
    Game* game = Game::Instance();

    since_last_shot += deltaTime;

    if (health <= 0) Die();

    if (position.y < win->GetGameSize().y/5*1.5) {
        velocity.y = 90;
    }
    else {
        float time = glfwGetTime();
        velocity.x = cos(time)*30;
        velocity.y = sin(time)*30;
        int frame = renderer->GetAnimationHandler()->GetFrame();
        if (frame == 3) velocity.y = -200.f;
        else velocity.y = 200.f/5;
        if (since_last_shot >= shoot_cooldown && int(time)%5 != 2){
            Shoot();
        }
    }

    position += velocity*deltaTime;
    
    UpdateCurrentAnim();
    GameObjectPro::Update(deltaTime);
    hit_this_frame = false;
}

void Beholder::UpdateCurrentAnim()
{    
    if (hit_this_frame) color = vec3(1.0, 0.3, 0.3);
    else color = vec3(1.0);
}

void Beholder::Move(float deltaTime)
{
}

void Beholder::Shoot()
{
    Game* game = Game::Instance();
    float time = glfwGetTime()*0.6;
    if (int(time)%5 == 0) time *= 0;
    if (int(time)%5 == 3) time *= -1;
    int n = 7;

    for (int i = 0; i < n; i++) {
        float ang_off = M_PI*2.f/n*i;

        if (int(time)%10 == 1) {
            int m = 10;
            float a = 2*M_PI / m;
            float patt_rad = 15;
            for (int j = 0; j < m; j++) {
                float ang = j*a;
                vec2 offset = vec2(cos(ang), sin(ang))*patt_rad;
                vec2 dir = Game::Instance()->player->position - position;
                if (dir != vec2(0.0)) dir = normalize(dir);
                Game::Instance()->enemyBullets.push_back(new CirlcePatternBullet(
                    position+size*0.5f+vec2(0, -size.y/3)+offset,
                    dir,
                    Assets::enemyBulletTexture,
                    ang,
                    patt_rad
                ));
            }
        }
        else {
            game->enemyBullets.push_back(new StraightEnemyBullet(position+size*0.5f+vec2(0, -size.y/3), vec2(cosf(time+ang_off), sinf(time+ang_off))));
        }
    }
    since_last_shot = 0.f;
}

void Beholder::Draw() {

    Enemy::Draw();
    TextRenderer::Instance()->DrawText(
        "beholder", position+size*vec2(0.5, 0)+vec2(0, -13), 0.5, true, true, vec3(1.0)
    );
    Game* game = Game::Instance();

    vec2 dir = game->player->position+game->player->size*0.5f - position-size*0.5f;
    if (dir != vec2(0.0)) dir = normalize(dir);

    vec2 eyeBallPos = position+size*vec2(0.5, 0.54);
    vec2 eyeSize = vec2(10);

    UserInterface::UiRendererInstance()->DrawSprite(
        ResourceManager::GetTexture(Assets::eyeTexture), 
        eyeBallPos-eyeSize*0.5f+dir*4.f,
        eyeSize,
        0.f, vec3(1.0)
    );
}
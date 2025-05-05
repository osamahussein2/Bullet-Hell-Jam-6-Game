#include "Player.h"
#include "Input.h"
#include "Game.h"
#include "Bullet.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Player::OnCollide(Body *other)
{
    if (state != PL_ST_HIT) {
        if (GameObjectPro* oth = dynamic_cast<GameObjectPro*>(other)){
            velocity = oth->velocity;
        }
    }
    hit_this_frame = true;
}

Player::Player(vec2 pos_) : ShootingObject(pos_, vec2(56, 56), Assets::playerTexture, 0.2) {
    renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
    const int columns = 6;
    const int rows = 5;

    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_IDLE, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_RIGHT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_LEFT, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_SPIN, 6, 6.f});
    renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_SHOOT, 6, 6.f});

    float coll_r = 10;
    collisions.push_back(new CircleCollision(coll_r, vec2(coll_r, coll_r+size.x/2)));
}

void Player::Update(float deltaTime)
{
    vec2 direction = vec2(0.0);

    if (hit_this_frame){
        if (state != PL_ST_HIT) {
            Game::Instance()->playerAura -= 0.1;
        }
        state = PL_ST_HIT;
        color = vec3(1.0, 0.0, 0.0);
    }
    else if (Input::IsKeyDown(GLFW_KEY_SPACE)) {
        state = PL_ST_SHOOT;
        color = vec3(1.0, 1.0, 1.0);
    }

    switch (state) {
    case PL_ST_IDLE:
        direction = HandleMovementInput();
        if (direction.x != 0) state = PL_ST_MOVE;
        break;

    case PL_ST_MOVE:
        direction = HandleMovementInput();
        if (direction.x == 0) state = PL_ST_IDLE;
        break;

    case PL_ST_HIT:
        direction = HandleMovementInput() * 0.5f;
        if (!hit_this_frame) {
            if (renderer->GetAnimationHandler()->GetCurrentAnimationData().current_frame == renderer->GetAnimationHandler()->GetCurrentAnimationData().frames-1) {
                state = PL_ST_IDLE;
                color = vec3(1.0, 1.0, 1.0);
            }
        }
        break;

    case PL_ST_SHOOT:
        direction = HandleMovementInput();
        if (Input::IsKeyDown(GLFW_KEY_SPACE)) {
            if (since_last_shot >= shoot_cooldown){
                Shoot();
            }
        }
        else {
            state = PL_ST_IDLE;
        }
        break;
    }

    velocity += direction * acceleration * deltaTime;
    velocity *= std::max(0.0f, 1.0f - drag * deltaTime);
    position += velocity * deltaTime;

    since_last_shot += deltaTime;

    UpdateCurrentAnim();

    GameObjectPro::Update(deltaTime);

    hit_this_frame = false;
}

void Player::UpdateCurrentAnim() {
    switch (state) {
    case PL_ST_IDLE:
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_IDLE);
        break;
    case PL_ST_MOVE:
        if (velocity.x > 0) renderer->GetAnimationHandler()->SetCurrentAnim(PL_RIGHT);
        else if (velocity.x < 0) renderer->GetAnimationHandler()->SetCurrentAnim(PL_LEFT);
        break;
    case PL_ST_HIT:
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_SPIN);
        break;
    case PL_ST_SHOOT:
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_SHOOT);
        break;
    }
}

vec2 Player::HandleMovementInput()
{
    vec2 direction = vec2(0.0f);    

    if (Input::IsKeyDown(GLFW_KEY_W) || Input::IsKeyDown(GLFW_KEY_UP)) {

        direction.y = -1.0f;
    }
    if (Input::IsKeyDown(GLFW_KEY_S) || Input::IsKeyDown(GLFW_KEY_DOWN)) {
        direction.y = 1.0f;
    }
    if (Input::IsKeyDown(GLFW_KEY_A) || Input::IsKeyDown(GLFW_KEY_LEFT)) {
        direction.x = -1.0f;
    }
    if (Input::IsKeyDown(GLFW_KEY_D) || Input::IsKeyDown(GLFW_KEY_RIGHT)) {
        direction.x = 1.0f;
    }
	if (direction != vec2(0.f)) direction = normalize(direction);
    return direction;
}

void Player::Shoot()
{
    Game::Instance()->playerBullets.push_back(new PlayerBullet(position+vec2(size.x/2, 0.0), vec2(0.0, -1.0)));
    Game::Instance()->playerBullets.push_back(new PlayerBullet(position+vec2(size.x/2, 0.0), vec2(cos(M_PI/2+M_PI/9), -sin(M_PI/2+M_PI/9))));
    Game::Instance()->playerBullets.push_back(new PlayerBullet(position+vec2(size.x/2, 0.0), vec2(cos(M_PI/2-M_PI/9), -sin(M_PI/2-M_PI/9))));
    since_last_shot = 0.f;
}

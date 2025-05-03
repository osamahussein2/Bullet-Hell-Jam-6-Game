#include "Player.h"
#include "Input.h"

void Player::Update(float deltaTime)
{
    vec2 direction = vec2(0.0f);
    // Move the player around the game
    
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
	velocity = direction * speed;
    position += velocity * deltaTime;

    UpdateCurrentAnim();
    renderer->UpdateAnimation(deltaTime);
}

void Player::UpdateCurrentAnim() {
    if (velocity.x > 0) {
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_RIGHT);
    }
    else if (velocity.x < 0) {
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_LEFT);
    }
    else {
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_IDLE);
    }

    if (Input::IsKeyDown(GLFW_KEY_SPACE)) {
        renderer->GetAnimationHandler()->SetCurrentAnim(PL_SHOOT);
    }
}
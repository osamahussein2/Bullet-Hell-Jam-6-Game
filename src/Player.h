#ifndef PLAYER_H
#define PLAYER_H

#include "GameObjectPro.h"
#include "Assets.h"

// match y_pos (from 0) in spritesheet
enum PlayerAnimations {
    PL_IDLE = 0, 
    PL_RIGHT = 1,
    PL_LEFT = 2,
    PL_SPIN = 3,
    PL_SHOOT = 4,
};

class Player : public GameObjectPro {
private:
    float speed = 200.f;
public:
    virtual void OnCollide(Body& other) {};

    Player(vec2 pos_) : GameObjectPro(pos_, vec2(56, 56), Assets::playerTexture) {
        renderer = new SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, true);
        const int columns = 6;
        const int rows = 5;

        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_IDLE, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_RIGHT, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_LEFT, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_SPIN, 6, 6.f});
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ columns, rows, PL_SHOOT, 6, 6.f});
    }

    virtual void Update(float deltaTime) override;
    virtual void UpdateCurrentAnim() override;

};

#endif
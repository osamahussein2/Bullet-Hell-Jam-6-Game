#ifndef EFFECT_H
#define EFFECT_H

#include "GameObjectPro.h"
#include "Assets.h"

class Effect : public GameObjectPro {

private:
    float delay;
    float timer = 0.f;

public:
    Effect(float delay_, vec2 pos_, vec2 size_, unsigned sprite_) : delay(delay_), GameObjectPro(pos_, size_, sprite_) {}

    
    virtual void Draw() override {
        if (timer >= delay) {
            GameObjectPro::Draw();
        }
    }
     
    virtual void Update(float deltaTime) override {
        timer += deltaTime;
        GameObjectPro::Update(deltaTime);

        if (timer >= delay) {
            if (!renderer->GetAnimationHandler()->GetCurrentAnimationData()->playing) {
                ResourceManager::GetSound(Assets::explosionSound)->Play();
                renderer->GetAnimationHandler()->GetCurrentAnimationData()->playing = true;
            }
        }

        if (renderer->GetAnimationHandler()->AnimEnded()) {
            destroyed = true;
        }   
    }
    

    virtual void UpdateCurrentAnim() override {}
    virtual void OnCollide(Body* other) override {}
};

class Explosion : public Effect {

public:
    Explosion(float delay_, vec2 pos_) : Effect(delay_, pos_, glm::vec2(32.f), Assets::explosionTexture) {
        renderer = new SpriteRenderer(
            ResourceManager::GetShader(Assets::spriteShader),
            false, false, true
        );
        renderer->GetAnimationHandler()->AddAnimation(AnimationData{ 6, 1, 0, 4, 9.f, false, false});
    }
};

#endif
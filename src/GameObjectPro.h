#ifndef GAME_OBJECT_PRO_H
#define GAME_OBJECT_PRO_H

#include "Collisions.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

class GameObjectPro : public Body, public GameObject {
protected:
    SpriteRenderer* renderer;

public:
    ~GameObjectPro() {
        delete renderer;
    }

    GameObjectPro(vec2 pos_, vec2 size_, unsigned int sprite_) : Body(), GameObject(pos_, size_, sprite_, vec3(1.0), vec2(0.0)) {}

    virtual void Update(float deltaTime) {
        body_position = position;
        UpdatePositions();
        renderer->UpdateAnimation(deltaTime);
    }

    void Draw() {
        DrawSprite(*renderer);
    }

    virtual void UpdateCurrentAnim() = 0;

};

#endif
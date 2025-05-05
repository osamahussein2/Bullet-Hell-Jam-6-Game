#ifndef GAME_OBJECT_PRO_H
#define GAME_OBJECT_PRO_H

#include "Collisions.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "DebugDraw.h"
#include "Input.h"

class GameObjectPro : public Body, public GameObject {
protected:
    SpriteRenderer* renderer;

public:
    ~GameObjectPro() {
        if (!renderer){
            std::cerr << "In GameObjectPro destructor renderer is not valid to delete\n";
        }
        delete renderer;
    }

    GameObjectPro(vec2 pos_, vec2 size_, unsigned int sprite_) : Body(), GameObject(pos_, size_, sprite_, vec3(1.0), vec2(0.0)) {
        position -= size*0.5f;
    }

    virtual void Update(float deltaTime);

    void Draw();

    void DebugDraw();

    virtual void UpdateCurrentAnim() = 0;

};

#endif
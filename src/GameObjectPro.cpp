#include "GameObjectPro.h"

void GameObjectPro::Update(float deltaTime) {
    body_position = position;
    UpdatePositions();
    renderer->UpdateAnimation(deltaTime);
}

void GameObjectPro::Draw() {
    DrawSprite(*renderer);
    DebugDraw();
}

void GameObjectPro::DebugDraw() {
    if (Debug::debugSprite) Debug::Instance()->DrawRectangle(position, size);
    if (Debug::debugCollisions) {
        for (Collision* collision : collisions) {
            if (CircleCollision* circle = dynamic_cast<CircleCollision*>(collision)) {
                Debug::Instance()->DrawCircle(circle->center, circle->radius);
            }
        }
    }
}
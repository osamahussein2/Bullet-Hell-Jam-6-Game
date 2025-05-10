#include "Enemy.h"
#include "Game.h"
#include "Effect.h"

void Enemy::Die() {
    destroyed = true;
    float dx = 25.f;
    float dy = 25.f;

    for (float x = 0; x < size.x; x+=dx ) {
        for (float y = 0; y < size.y; y+=dy) {
            float rn1 = (double)std::rand() / (RAND_MAX);
            float rn2 = (double)std::rand() / (RAND_MAX);
            rn1 /= rn2;
            if ( rn1 > 0.5f) {
                Game::Instance()->effects.push_back(new Explosion(
                    rn2 * 0.7f,
                    vec2(position.x+x, position.y+y)
                ));
            }
        }
    }
}
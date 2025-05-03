#ifndef BULLET_H
#define BULLET_H

#include "GameObjectPro.h"

class Bullet : public GameObjectPro {

public:
    Bullet(vec2 pos_, vec2 size_, unsigned int sprite_) : GameObjectPro(pos_, size_, sprite_) {}

};

#endif
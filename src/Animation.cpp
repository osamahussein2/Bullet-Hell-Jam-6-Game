#include "Animation.h"
#include <iostream>

void Animation::Update(float deltaTime){
    if (anims.size() == 0){
        std::cerr << "no animations to play\n";
    }
    
    AnimationData& anim = anims[current_anim];

    anim.frame_count++;    
    if (anim.frame_count >= (1.f / (anim.fps*deltaTime) )) {
        anim.frame_count = 0;
        anim.current_frame = (anim.current_frame + 1) % anim.frames;
    }
}
#include "Animation.h"
#include <iostream>

void Animation::Update(float deltaTime){
    if (anims.size() == 0){
        std::cerr << "no animations to play\n";
    }
    
    AnimationData& anim = anims[current_anim];

    if (anim.playing) {
        if (anim.looping || !anim.reached_end) {
            anim.frame_count++;
        }
        
        if (anim.frame_count >= (1.f / (anim.fps*deltaTime) )) {
            anim.frame_count = 0;
            anim.current_frame++;
            if (anim.looping) {
                anim.current_frame %= anim.frames;
            }
            else {
                if (anim.current_frame >= anim.frames) {
                    anim.reached_end = true;
                    anim.current_frame--;
                }
            }
            if (qued_anim != -1) {
                anim.current_frame = 0;
                current_anim = qued_anim;
                AnimationData& anim = anims[current_anim];
                qued_anim = -1;
                anim.frame_count = 0;
                anim.current_frame = 0;
            }
        }
    }
}
#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <iostream>

struct AnimShaderUniforms {
    int columns_loc;
    int rows_loc;
    int current_frame_loc;
};

struct AnimationData {
	// how spritesheet is split
	int columns;
	int rows;

    // the location of this particular anim
    int y_pos = 0;
    int frames;

	// playing
	float fps;

    bool looping = true;
    bool playing = true;
    bool reached_end = false;

    float frame_count = 0.f;
    int current_frame = 0;


    int GetStartFrame() {
        return y_pos * columns;
    }
};

struct FrameData {
	int columns;
	int rows;
    int frame;
};

class Animation {
private:
    std::vector<AnimationData> anims = {};
	int current_anim = 0;
    int qued_anim = -1;
    
public:
    void Update(float deltaTime);

    // for drawing
    FrameData GetCurrentFrameData() {
        return FrameData{
            anims[current_anim].columns,
            anims[current_anim].rows,
            anims[current_anim].GetStartFrame() + anims[current_anim].current_frame
        };
    }

    AnimationData* GetCurrentAnimationData() {
        return &anims[current_anim];
    }

    void AddAnimation(AnimationData anim){ anims.push_back(anim); }

    void RestartAnim(int anim_) {
        anims[anim_].reached_end = false;
        anims[anim_].frame_count = 0;
        anims[anim_].current_frame = 0;
    }

    void SetCurrentAnim(int current_anim_){
        if (current_anim != current_anim_) {
            anims[current_anim].frame_count = 0;
            anims[current_anim].current_frame = 0;
        }
        current_anim = current_anim_;
    }
    void QueueAnim(int queue_anim_){ qued_anim = queue_anim_; }
    int GetCurrentAnim(){ return current_anim; }
    int GetNumberOfAnims() { return anims.size(); }

    void SetFrame(int frame_) { anims[current_anim].current_frame = frame_; }
    void SetFrameCount(int frame_count_) { anims[current_anim].frame_count = frame_count_; }

    bool AnimEnded() { return anims[current_anim].reached_end; }
    int GetFrame() { return anims[current_anim].current_frame; }
};

#endif
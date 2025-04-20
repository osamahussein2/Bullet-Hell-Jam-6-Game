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
    
public:
    void Update(float deltaTime);
    
    FrameData GetCurrentFrame() {
        return FrameData{
            anims[current_anim].columns,
            anims[current_anim].rows,
            anims[current_anim].GetStartFrame() + anims[current_anim].current_frame
        };
    }

    void AddAnimation(AnimationData anim){ anims.push_back(anim); }

    void SetCurrentAnim(int current_anim_){ current_anim = current_anim_; }
    int GetCurrentAnim(){ return current_anim; }
    int GetNumberOfAnims() { return anims.size(); }
};

#endif
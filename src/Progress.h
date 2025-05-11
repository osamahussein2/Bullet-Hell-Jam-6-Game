#ifndef PROGRESS_H
#define PROGRESS_H

#include <vector>
#include "glm.hpp"
#include "Assets.h"
#include "Window.h"

struct Stage {
    Stage(int music_enum_ = Assets::HellHole, vec2 arenaSize_ = vec2(640, 360)) : music_enum(music_enum_), arenaSize(arenaSize_) {}
    vec2 arenaSize;
    int music_enum;
    bool cleared = false;
    float timer;
    virtual void Load() {
        timer = 0.f;
        ResourceManager::PlayMusic(music_enum);
    };
    virtual void Update(float deltaTime, bool canProceed = true);
};

struct Level {
    Level(std::vector<Stage*> stages_) : stages(stages_) {}
    ~Level() {
        for (Stage* stage : stages) {
            delete stage;
        }
        stages.clear();
    }

    std::vector<Stage*> stages;
    int currentStage = 0;
    
    Stage* GetCurrentStage() {
        return stages[currentStage];
    }

    void Load() { stages[currentStage]->Load(); }

    bool GoNext() {
        currentStage++;
        if (currentStage >= stages.size()) {
            return true;
        }
        else {
            return false;
        }
    }

    virtual Level* GetNextLevel() = 0;
};

/************************************************************** */

struct Stage1_1 : Stage {
    virtual void Load() override;
};
struct Stage1_2 : Stage {
    virtual void Load() override;
};

struct BeholderFight : Stage {
    BeholderFight() : Stage(Assets::LTHAWFD) {}
    bool spawnedBoss = false;
    virtual void Load() override;
    virtual void Update(float deltaTime, bool canProceed) override;
};

struct BigBoyFight : Stage {
    BigBoyFight() : Stage(Assets::LTHAWFD) {}
    bool spawnedBoss = false;
    virtual void Load() override;
    virtual void Update(float deltaTime, bool canProceed) override;
};

struct Level1 : Level {
    Level1();
    virtual Level* GetNextLevel() override;
};

struct Level2 : Level {
    Level2();
    virtual Level* GetNextLevel() override;
};

struct Stage2_1 : Stage {
    Stage2_1() : Stage(Assets::HellHole, 2.f*vec2(640, 360)) {}
    virtual void Load() override;
};
struct Stage2_2 : Stage {
    Stage2_2() : Stage(Assets::HellHole, 2.f*vec2(640, 360)) {}
    virtual void Load() override;
};

/************************************************************** */

struct Progress {
    Level* currentLevel;

    Progress() : currentLevel(new Level1()){}
    ~Progress() {
        delete currentLevel;
    }

    void Load() { currentLevel->Load(); }

    void Update(float deltaTime) {
        currentLevel->stages[currentLevel->currentStage]->Update(deltaTime);
    }

    void GoNext();
};



#endif
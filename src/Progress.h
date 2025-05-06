#ifndef PROGRESS_H
#define PROGRESS_H

#include <vector>
#include "glm.hpp"

struct Stage {
    virtual void Load() = 0;
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

struct Level1 : Level {
    Level1();
    virtual Level* GetNextLevel() override;
};

struct Level2 : Level {
    Level2();
    virtual Level* GetNextLevel() override;
};

/************************************************************** */

struct Progress {
    Level* currentLevel;

    Progress() : currentLevel(new Level1()){}
    ~Progress() {
        delete currentLevel;
    }

    void Load() { currentLevel->Load(); }

    void GoNext() {
        if (currentLevel->GoNext()) {
            if (Level* next = currentLevel->GetNextLevel()) {
                delete currentLevel;
                currentLevel = next;
            }
            else {
                // GAME WON HERE
                delete currentLevel;
                currentLevel = new Level1();
            }
        }
    };
};



#endif
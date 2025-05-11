#include "Progress.h"
#include "Game.h"
#include "Window.h"
#include "Assets.h"

#include "CultistBasic.h"
#include "Bomba.h"
#include "Summoner.h"
#include "Orb.h"
#include "Beholder.h"
#include "BigBoy.h"
#include "Player.h"
#include "Effect.h"

void Stage::Update(float deltaTime, bool canProceed) {
    auto g = Game::Instance();
    timer += deltaTime;
    if (g->enemies.size() == 0 && canProceed) {
        timer += deltaTime; // faster background
        if (!cleared) ResourceManager::GetSound(Assets::ProgressSound)->Play();
        cleared = true;
        vec2 s = Window::Instance()->GetGameSize();
        vec2 d = s*vec2(0.5, -1) - g->player->position;
        g->player->velocity = normalize(d)*400.f;
		if (glm::length(d) < s.y/2) {
            g->canFinish = true;
        }
    }
    else {
        g->player->position.x = glm::clamp(g->player->position.x, 0.0f, arenaSize.x-g->player->size.x);
        g->player->position.y = glm::clamp(g->player->position.y, 0.0f, arenaSize.y-g->player->size.y);
    }
};



void Stage1_1::Load()
{
    Stage::Load();
    Game* game = Game::Instance();
	vec2 center = Window::Instance()->GetGameSize()*0.5f;
	game->player->position = center+vec2(0, center.y);

    //game->enemies.push_back(new Bomba(center + vec2(150, -80)));

	// must be careful, enemies must be initially in their movement range
	//game->enemies.push_back(new CultistBasic(vec2(center.x, 80)));
	game->enemies.push_back(new CultistBasic(vec2(center.x, center.y-50)));
	//game->enemies.push_back(new CultistBasic(vec2(center.x*2-80, 120)));
}

void Stage1_2::Load()
{
    Stage::Load();
    Game* game = Game::Instance();
	vec2 center = Window::Instance()->GetGameSize()*0.5f;
	game->player->position = center+vec2(0, center.y);

    game->enemies.push_back(new Summoner(vec2(169, center.y-40)));

    game->enemies.push_back(new Bomba(center));
}

void BeholderFight::Load()
{
    spawnedBoss = false;

    Stage::Load();
    Game* game = Game::Instance();
	vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
	game->player->position = center+vec2(0, center.y);

    game->enemies.push_back(new Orb(vec2(100, 100)));

    game->enemies.push_back(new Summoner(center+center*vec2(-0.2, -0.2)));
    game->enemies.push_back(new CultistBasic(center+center*vec2(0.2, -0.2)));

    game->enemies.push_back(new Orb(center*2.f+vec2(-100, -200)));
}

void BeholderFight::Update(float deltaTime, bool canProceed)
{
    Stage::Update(deltaTime, spawnedBoss);
    if (timer >= 27.7 && !spawnedBoss) {
        //timer += 10000;
        spawnedBoss = true;

        Game* game = Game::Instance();
        game->KillAllEnemies();

        vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
        game->enemies.push_back(new Beholder(vec2(center.x, 0)));
    }
}


void BigBoyFight::Load()
{
    spawnedBoss = false;

    Stage::Load();
    Game* game = Game::Instance();
	vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
	game->player->position = center+vec2(0, center.y);

    Game::Instance()->enemies.push_back(new Bomba(center));

    Game::Instance()->enemies.push_back(new CultistBasic(center + vec2(0, -60)));

    Game::Instance()->enemies.push_back(new Orb(center + vec2(200, -80)));
    Game::Instance()->enemies.push_back(new Orb(center + vec2(-200, -80)));

    Game::Instance()->enemies.push_back(new Orb(center + vec2(100, 80)));
    Game::Instance()->enemies.push_back(new Orb(center + vec2(-100, 80)));

}

void BigBoyFight::Update(float deltaTime, bool canProceed)
{
    Stage::Update(deltaTime, spawnedBoss);
    if (timer >= 27.7 && !spawnedBoss) {
        spawnedBoss = true;

        Game* game = Game::Instance();
        game->KillAllEnemies();

        vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
        game->enemies.push_back(new BigBoy(vec2(center.x, 0)));
    }
}

Level1::Level1() : Level( { new Stage1_1(), new Stage1_2(), new BigBoyFight() } ) {}

Level *Level1::GetNextLevel()
{
    return new Level2();
}

Level2::Level2() : Level(

    {
        new Stage2_1(), new Stage2_2(), new BeholderFight()
    }

) {}

Level *Level2::GetNextLevel()
{
    return nullptr;
}

void Stage2_1::Load()
{
    Stage::Load();
    Game* game = Game::Instance();
    vec2 center = Window::Instance()->GetGameSize() * 0.5f;
    game->player->position = center + vec2(0, center.y);

    //game->enemies.push_back(new Bomba(center + vec2(150, -80)));

    // must be careful, enemies must be initially in their movement range
    //game->enemies.push_back(new CultistBasic(vec2(center.x, 80)));
    game->enemies.push_back(new Summoner(vec2(200, center.y - 40)));
    game->enemies.push_back(new CultistBasic(vec2(300, center.y - 40)));
    game->enemies.push_back(new CultistBasic(vec2(500, center.y - 40)));
    //game->enemies.push_back(new CultistBasic(vec2(center.x*2-80, 120)));
}

void Stage2_2::Load()
{
    Stage::Load();
    Game* game = Game::Instance();
    vec2 center = Window::Instance()->GetGameSize() * 0.5f;
    game->player->position = center + vec2(0, center.y);

    game->enemies.push_back(new Summoner(vec2(200, center.y - 40)));
    game->enemies.push_back(new CultistBasic(vec2(300, center.y - 40)));
    game->enemies.push_back(new Bomba(center));
}
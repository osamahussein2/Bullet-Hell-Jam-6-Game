#include "Progress.h"
#include "Game.h"
#include "Window.h"

#include "CultistBasic.h"
#include "Bomba.h"
#include "Summoner.h"
#include "Orb.h"
#include "Player.h"

void Stage1_1::Load()
{
    Game* game = Game::Instance();
	vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
	game->player->position = center;

    game->enemies.push_back(new Bomba(center + vec2(150, -80)));

	// must be careful, enemies must be initially in their movement range
	game->enemies.push_back(new CultistBasic(vec2(center.x, 80)));
	game->enemies.push_back(new CultistBasic(vec2(80, 120)));
	game->enemies.push_back(new CultistBasic(vec2(center.x*2-80, 120)));
}

void Stage1_2::Load()
{
    Game* game = Game::Instance();
	vec2 center = vec2(Window::Instance()->GetGameSize().x/2, Window::Instance()->GetGameSize().y/2);
	game->player->position = center;

    game->enemies.push_back(new Summoner(center+vec2(0, -100)));
}

Level1::Level1() : Level( { new Stage1_1(), new Stage1_2(), new Stage1_2(), new Stage1_2(), new Stage1_2() } ) {}

Level *Level1::GetNextLevel()
{
    return new Level2();
}

Level2::Level2() : Level(

    {
        new Stage1_1()
    }

) {}

Level *Level2::GetNextLevel()
{
    return nullptr;
}

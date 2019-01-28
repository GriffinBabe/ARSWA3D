#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "Entity.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	std::vector<Entity*>* getEntities();
	void game_loop(float delta_time);

	Player* getLocalPlayer();
private:

	Player* localPlayer;
	std::vector<Player*>* players;
	std::vector<Entity*>* entities;
	Map* map;
};

#endif
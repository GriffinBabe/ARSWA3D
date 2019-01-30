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

	std::vector<SolidEntity*>* getEntities();
	std::vector<SolidEntity*>* get_map_collidables();
	std::vector<Entity*>* get_map_decorations();

	Map* get_map();

	void game_loop(float delta_time);

	Player* getLocalPlayer();

private:

	Player* localPlayer;
	std::vector<Player*>* players;
	std::vector<SolidEntity*>* entities;
	Map* map;
};

#endif
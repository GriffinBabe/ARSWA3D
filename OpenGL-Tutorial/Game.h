#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "Entity.h"
#include "Player.h"
#include "CommandManager.h"
#include "MovementManager.h"


class Game
{
public:
	Game();
	~Game();

	Player* getLocalPlayer();

	/**
		Main game loop
	*/
	void game_loop(float delta_time);

	/**
		Adds a command to our CommandManager.
	*/
	void addCommand(Command* command);

private:

	Player* localPlayer;
	std::vector<Player*> players;
	std::vector<Entity*> entities;
	Map* map;

	CommandManager commandManager;
	MovementManager movementManager;

};

#endif
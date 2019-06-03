#include "Game.h"
#include "Command.h"

Game::Game() : entities(std::vector<Entity*>()), players(std::vector<Player*>())
{
	// Loads all our entities from the map and puts them into our game.
	this->map = new Map();
	for (auto* n : map->getEntities()) {
		entities.push_back(n);
	}

	// Creates a local player and attach the Model to it.
	this->localPlayer = new Player(this, 0.0f, 0.0f);
	ModelList::attachCharacter(this->localPlayer->getCharacter());

	entities.push_back(this->localPlayer->getCharacter());
	players.push_back(this->localPlayer);

	commandManager = CommandManager();
	movementManager = MovementManager(this->map->boundary_bottom,
		this->map->boundary_left, this->map->boudary_right, this->map->boundary_top);
}

Game::~Game()
{
	delete map;
	delete localPlayer;
}

void Game::game_loop(float delta_time)
{
	commandManager.loop(delta_time);
	movementManager.loop(&entities, delta_time);
}

void Game::addCommand(Command * command)
{
	commandManager.addCommand(command);
}

Player * Game::getLocalPlayer()
{
	return this->localPlayer;
}
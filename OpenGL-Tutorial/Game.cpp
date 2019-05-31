#include "Game.h"
#include "Command.h"

Game::Game()
{

	this->entities = new std::vector<SolidEntity*>();
	this->players = new std::vector<Player*>();

	// Loads all our entities from the map and puts them into our game.
	this->map = new Map();
	for (auto* n : *map->get_collision_entities()) {
		entities->push_back(n);
	}
	this->localPlayer = new Player(this, 0.0f, 0.0f);

	std::cout << this->localPlayer->getCharacter()->width << " " << this->localPlayer->getCharacter()->height << std::endl;

	this->entities->push_back(this->localPlayer->getCharacter());
	this->players->push_back(this->localPlayer);

	commandManager = CommandManager();
	movementManager = MovementManager(this->entities, this->map->boundary_bottom,
		this->map->boundary_left, this->map->boudary_right, this->map->boundary_top);
}

Game::~Game()
{
	delete map;
	delete localPlayer;
	delete entities;
	delete players;
}

std::vector<SolidEntity*>* Game::getEntities()
{
	return this->entities;
}

std::vector<SolidEntity*>* Game::get_map_collidables()
{
	return this->map->get_collision_entities();
}

std::vector<Entity*>* Game::get_map_decorations()
{
	return this->map->get_decorative_entities();
}

Map * Game::get_map()
{
	return this->map;
}

void Game::game_loop(float delta_time)
{
	commandManager.loop(delta_time);
	movementManager.loop(delta_time);

}

void Game::addCommand(Command * command)
{
	commandManager.addCommand(command);
}

Player * Game::getLocalPlayer()
{
	return this->localPlayer;
}
#include "Game.h"



Game::Game()
{

	this->entities = new std::vector<SolidEntity*>();
	this->players = new std::vector<Player*>();

	//NOTE: There are entities here too!
	this->map = new Map();
	this->localPlayer = new Player(this, 0.0f, 0.0f);

	std::cout << this->localPlayer->getCharacter()->width << " " << this->localPlayer->getCharacter()->height << std::endl;

	this->entities->push_back(this->localPlayer->getCharacter());
	this->players->push_back(this->localPlayer);
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
	//std::cout << this->localPlayer->getCharacter()->x << " " << this->localPlayer->getCharacter()->y << " " << this->localPlayer->getCharacter()->z << std::endl;
	for (Player* p : *this->players) {
		p->getCharacter()->loop(delta_time);
	}
}

Player * Game::getLocalPlayer()
{
	return this->localPlayer;
}
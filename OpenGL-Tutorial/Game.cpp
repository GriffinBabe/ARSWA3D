#include "Game.h"



Game::Game()
{
	this->localPlayer = new Player(0.0f, 0.0f);

	this->entities = new std::vector<Entity*>();
	this->players = new std::vector<Player*>();

	//NOTE: There are entities here too!
	this->map = new Map();
	
	this->entities->push_back(this->localPlayer->getCharacter());
	this->players->push_back(this->localPlayer);
}


Game::~Game()
{
}

std::vector<Entity*>* Game::getEntities()
{
	return this->entities;
}

std::vector<Entity*>* Game::get_map_collidables()
{
	return this->map->get_collision_entities();
}

std::vector<Entity*>* Game::get_map_decorations()
{
	return this->map->get_decorative_entities();
}

void Game::game_loop(float delta_time)
{
	for (Player* p : *this->players) {
		p->getCharacter()->loop(delta_time);
	}
}

Player * Game::getLocalPlayer()
{
	return this->localPlayer;
}
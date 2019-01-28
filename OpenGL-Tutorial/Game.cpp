#include "Game.h"



Game::Game()
{
	this->localPlayer = new Player(0.0f, 0.0f);

	this->entities = new std::vector<Entity*>();
	this->players = new std::vector<Player*>();

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

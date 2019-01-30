#include "Player.h"
#include "Game.h"


Player::Player(Game* game, float x, float y)
{
	this->character = new Witch(game, x, y);
}


Player::~Player()
{
}

Character * Player::getCharacter()
{
	return this->character;
}
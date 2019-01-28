#include "Player.h"
#include "Game.h"


Player::Player(float x, float y)
{
	this->character = new Witch(x, y);
}


Player::~Player()
{
}

Character * Player::getCharacter()
{
	return this->character;
}
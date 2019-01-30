#ifndef PLAYER_H
#define PLAYER_H



#include <string>
#include "Witch.h"

class Game;

class Player
{
public:
	Player(Game* game, float x, float y);
	~Player();

	Character* getCharacter();
private:
	Character* character;
	std::string username;
	char teamColor;

};

#endif // !

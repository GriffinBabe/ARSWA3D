#ifndef COMMAND_H
#define COMMAND_H

#include "Mob.h"

class Game;

class Command
{
public:
	Command();
	virtual ~Command();

	virtual void execute() = 0;

};

class JumpCommand : public Command
{
private:
	Mob* mob;
public:
	JumpCommand(Mob* mob);
	~JumpCommand();

	void execute();
};

class DirectionCommand : public Command
{
private:
	Mob* mob;
	int direction = 0;
public:
	DirectionCommand(Mob* mob, int direction);
	~DirectionCommand();

	void execute();
};

#endif
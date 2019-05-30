#include "Command.h"
#include "Game.h"


Command::Command()
{
}


Command::~Command()
{
}

JumpCommand::JumpCommand(Mob* mob)
{
	this->mob = mob;
}

JumpCommand::~JumpCommand()
{
}

void JumpCommand::execute()
{
	mob->jump();
}

DirectionCommand::DirectionCommand(Mob * mob, int direction) : direction(direction)
{
	this->mob = mob;
}

DirectionCommand::~DirectionCommand()
{
}

void DirectionCommand::execute()
{
	mob->change_direction(direction);
}
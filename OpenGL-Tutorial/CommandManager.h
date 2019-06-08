#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <vector>
#include "Command.h"


/**
	Will manage the command, mostly by storing them into a command vector and execute those commands

	@Author: Darius Couchard
*/

class CommandManager
{
private:
	std::vector<Command*> commands;
public:
	CommandManager();
	~CommandManager();

	void loop(float delta_time);

	void addCommand(Command* com);
};
#endif


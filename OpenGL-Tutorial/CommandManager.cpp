#include "CommandManager.h"

CommandManager::CommandManager()
{
	commands = std::vector<Command*>();
}


CommandManager::~CommandManager()
{
}

void CommandManager::loop(float delta_time)
{
	unsigned int size = commands.size();
	for (unsigned int index = 0; index < commands.size(); index++) {
		commands[size-1]->execute();
		commands.pop_back(); // deletes last element
		size--;
	}
}

void CommandManager::addCommand(Command * com)
{
	commands.push_back(com);
}

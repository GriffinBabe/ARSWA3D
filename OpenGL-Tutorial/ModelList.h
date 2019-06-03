#ifndef MODELLIST_H
#define MODELLIST_H

#include "Model.h"
#include "Character.h"

class ModelList 
{
	public:
		static Model* witch;
		static Model* platform;
		static Model* roof;
		static Model* wall;

		static void Init();
		static void clear();
		~ModelList();
		
		static void attachCharacter(Character* character);
};

#endif // !MODELLIST_H

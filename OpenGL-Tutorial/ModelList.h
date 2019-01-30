#ifndef MODELLIST_H
#define MODELLIST_H

#include "Model.h"

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
		
};

#endif // !MODELLIST_H

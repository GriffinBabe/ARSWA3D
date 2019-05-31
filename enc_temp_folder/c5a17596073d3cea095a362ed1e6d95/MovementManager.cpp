#include "MovementManager.h"



MovementManager::MovementManager()
{
}


MovementManager::MovementManager(std::vector<SolidEntity*>* solid_entities, float bottom, float left, float right, float top)
	: bottomMap(bottom), leftMap(left), rightMap(right), topMap(top)
{
	this->solid_entities = solid_entities;
}

MovementManager::~MovementManager()
{
}


void MovementManager::loop(float delta_time)
{
	int movingEntitiesCount = 0;
	for (SolidEntity* entity : *solid_entities) {
		if (MovingEntity* m_entity = static_cast<MovingEntity*>(entity)) {
			movingEntitiesCount++;
			m_entity->accelerate(delta_time); // Changes the speedX with the acceleration direction etc.
			m_entity->move(delta_time); // Changes the position
			m_entity->checkMapBoundaries(bottomMap, leftMap, rightMap, topMap); // Checks if it hasn't crossed the map boundaries
			std::cout << solid_entities->size() << std::endl;
			for (SolidEntity* entity_to_collide : *solid_entities) { // Checks collisions.
				if (entity_to_collide->collidable && entity_to_collide != entity) {
					if (entity_to_collide->check_collision(m_entity)) {
						
						m_entity->hit(entity_to_collide);
					}
				}
			}
		}
	}
}
#include "MovementManager.h"



MovementManager::MovementManager()
{
}


MovementManager::MovementManager(float bottom, float left, float right, float top)
	: bottomMap(bottom), leftMap(left), rightMap(right), topMap(top)
{
}

MovementManager::~MovementManager()
{
}


void MovementManager::loop(std::vector<Entity*>* entities, float delta_time)
{
	int movingEntitiesCount = 0;
	for (Entity* entity : *entities) {
		if (MovingEntity* m_entity = dynamic_cast<MovingEntity*>(entity)) {
			movingEntitiesCount++;

			m_entity->accelerate(delta_time); // Changes the speedX with the acceleration direction etc.
			m_entity->move(delta_time); // Changes the position
			m_entity->checkMapBoundaries(bottomMap, leftMap, rightMap, topMap); // Checks if it hasn't crossed the map boundaries

			for (Entity* entity_to_collide : *entities) { // Checks collisions.
				if (SolidEntity* solidEntity = dynamic_cast<SolidEntity*>(entity_to_collide)) {
					if (solidEntity != entity) {
						if (solidEntity->check_collision(m_entity)) {
							m_entity->hit(solidEntity);
						}
					}
				}
			}
		}
	}
}
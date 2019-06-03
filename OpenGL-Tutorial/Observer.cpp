#include "Observer.h"
#include "Entity.h"

void Subject::addObserver(Observer * observer)
{
	observers.push_back(observer);
}

void Subject::removeObserver(Observer * observer)
{
	int index = 0;
	for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it, ++index) {
		if (*it == observer) {
			break;
		}
	}
	observers.erase(observers.begin() + index);
}

void Subject::notify(Entity & entity, EEvent event)
{
	for (Observer* obs : observers) {
		obs->onNotify(entity, event);
	}
}

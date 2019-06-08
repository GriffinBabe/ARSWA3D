#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Entity;
enum EEvent;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(Entity& entity, EEvent event) = 0;
};

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

private:
	std::vector<Observer*> observers;

protected:
	void notify(Entity & entity, EEvent event);

};

#endif

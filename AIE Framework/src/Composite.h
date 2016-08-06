#pragma once
#include "Behaviour.h"

//Base class for sequence and selector to inherit from
class Composite : public Behaviour
{
public:
	Composite();
	~Composite();

	virtual Status Execute(Agent* a_agent) = 0;

	void AddBehaviour(Behaviour* a_newBehaviour);
	void RemoveBehaviour(Behaviour* a_behaviourToRemove);

protected:
	std::list<Behaviour*> childBehaviours;
	Behaviour* pendingChild;
	Behaviour* child;
	Status result;
};


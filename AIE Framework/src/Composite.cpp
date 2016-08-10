#include "Composite.h"

Composite::Composite()
{
}


Composite::~Composite()
{
}

Behaviour::Status Composite::Execute(Agent * a_agent)
{
	//Checking where to start again this tick
	/*auto iter = childBehaviours.begin();

	for (; iter != childBehaviours.end(); iter++)
	{
		if ((*iter) == child)
		{

		}
	}*/

	return Status::BT_SUCCESS;
}

void Composite::AddBehaviour(Behaviour * a_newBehaviour)
{
	childBehaviours.push_back(a_newBehaviour);
}

void Composite::RemoveBehaviour(Behaviour * a_behaviourToRemove)
{
	auto iter = childBehaviours.begin();

	for (; iter != childBehaviours.end(); iter++)
	{
		if ((*iter) == a_behaviourToRemove)
		{
			childBehaviours.erase(iter);
		}
	}
}

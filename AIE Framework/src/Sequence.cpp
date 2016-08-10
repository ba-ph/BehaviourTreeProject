#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::~Sequence()
{
}

Sequence::Status Sequence::Execute(Agent * a_agent)
{

	//Need to find a new to switch to the next child if one fails

	/*child = pendingChild;
	pendingChild = nullptr;

	if (child == nullptr)
	{
		child = childBehaviours.front();
	}

	while (child <= childBehaviours.back())
	{
		result = child->Execute(a_agent);
		if (result == BT_SUCCESS)
		{
			return BT_SUCCESS;
		}
		if (result == BT_FAILURE)
		{
		//	child = next child;
		}
		if (result == BT_RUNNING)
		{
			pendingChild = child;
			return BT_RUNNING;
		}
	}*/

	//Iterate through all children in childBehaviours
	auto iter = childBehaviours.begin();
	for (; iter != childBehaviours.end(); iter++){

		//if child->Execute() fails
		if ((*iter)->Execute(a_agent) == Status::BT_FAILURE){
			//return Failure
			return Status::BT_FAILURE;
		}
		else{
			//else return Success
			Status::BT_SUCCESS;
		}
		
	}

	return Status::BT_SUCCESS;
}

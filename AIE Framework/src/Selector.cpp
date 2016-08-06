#include "Selector.h"



Selector::Selector()
{
}


Selector::~Selector()
{
}

Behaviour::Status Selector::Execute(Agent * a_agent)
{
	//Checking to see if there is a currently running leaf node
	//and if so continue from that node
	child = pendingChild;
	pendingChild = nullptr;

	if (child == nullptr) {
		child = childBehaviours.front();
	}

	if (child <= childBehaviours.back() )
	{

	}




	//Iterate through all children in childBehaviours
	auto iter = childBehaviours.begin();
	for (; iter != childBehaviours.end(); iter++) {

		//if child->Execute() 
		if ((*iter)->Execute(a_agent) == Status::BT_SUCCESS) {
			//return Success
			return Status::BT_SUCCESS;
		}
		else {
			//else return Failure
			Status::BT_FAILURE;
		}

	}
}

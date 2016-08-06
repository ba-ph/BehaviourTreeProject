#pragma once
#include "Agent.h"
#include <list>

//The interface class for all behaviour nodes
class Behaviour
{
public:
	Behaviour();
	~Behaviour();

	enum Status
	{
		BT_SUCCESS,
		BT_FAILURE,
		BT_RUNNING,
	};

	virtual Status Execute(Agent* a_agent) =0;


	Status getStatus() const;

private:
	Status m_eStatus;
};


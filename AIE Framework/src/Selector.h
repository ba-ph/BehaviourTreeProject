#pragma once
#include "Composite.h"

//'OR' Node for running a list of behaviours consecutively until one succeeds
class Selector : public Composite
{
public:
	Selector();
	~Selector();

	Behaviour::Status Execute(Agent* a_agent);

};


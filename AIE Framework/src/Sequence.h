#pragma once
#include "Composite.h"

//'AND' Node for running a list of behaviours consecutively until one fails
class Sequence : public Composite
{
public:
	Sequence();
	~Sequence();

	Status Execute(Agent* a_agent);

};


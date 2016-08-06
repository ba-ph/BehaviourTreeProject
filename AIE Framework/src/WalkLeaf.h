#pragma once
#include "Behaviour.h"

class Walk : public Behaviour
{
public:
	Walk();
	~Walk();

	//Called once when the parent first iterates over this node
	void Initialize();

	//Called each tick while node is processing 
	// if Success or Failure, processing ends and result returned to parent
	Behaviour::Status Execute(Agent* a_agent);

private:
	//Not really needed but helpful if testing with other entities
	Agent* m_characterReference;

	Vector2 m_destination;
};
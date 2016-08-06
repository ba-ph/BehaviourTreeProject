#include "WalkLeaf.h"

Walk::Walk()
{
}

Walk::~Walk()
{
}

void Walk::Initialize()
{

}

Behaviour::Status Walk::Execute(Agent * a_agent)
{
	//Calculate path to target if no current path
	if (a_agent->m_path.empty())
		a_agent->m_path = a_agent->GetGraphReference()->Dijkstra(a_agent->GetGraphReference()->GetClosestNode(a_agent->GetPosition()), a_agent->GetGraphReference()->GetClosestNode(a_agent->GetTarget()));

	//if not at the target yet
	if ((a_agent->GetPosition() - a_agent->GetTarget()).SqaureMagnitude() > 250.0f && a_agent->m_path.size() > 1)
		return BT_RUNNING;
	else if ((a_agent->GetPosition() - a_agent->GetTarget()).SqaureMagnitude() > 250.0f && a_agent->m_path.empty())
		return BT_SUCCESS;
	else
		return BT_FAILURE;

	//Walk to target returning Status::BT_RUNNING each tick until target has been reached 
	// Returning Status::BT_SUCCESS, otherwise return Status::BT_FALSE
}

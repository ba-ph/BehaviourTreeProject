#include "WalkLeaf.h"

Walk::Walk()
{
	PathFinished = true;
}

Walk::~Walk()
{
}

void Walk::Initialize()
{

}

Behaviour::Status Walk::Execute(Agent * a_agent)
{

	if ((a_agent->GetPosition().SqrDistance(a_agent->GetTarget()) < 10.0f ))
	{
		PathFinished = true;
		ClearPath(a_agent);
		a_agent->SetTarget(nullptr);
	}

	//seek to path
	if (a_agent->m_path.empty() == false) {
		auto pathBegin = a_agent->m_path.begin();

		//calculate force vector
		Vector2 vecBetweenAgentTarget = a_agent->GetTarget() - *a_agent->m_path.begin();
		Vector2 force = vecBetweenAgentTarget.Normalized() * a_agent->m_maxVelocity;

		//Add the force
		a_agent->AddForce(force - a_agent->m_velocity);
	}

	//Calculate path to target if no current path
	if (a_agent->m_path.empty() && a_agent->GetTarget() != nullptr)
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

void Walk::ClearPath(Agent* a_agent)
{
	a_agent->m_path.clear();
}

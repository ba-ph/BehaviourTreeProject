#include "Agent.h"
#include "BaseEntity.h"
#include "Behaviour.h"
#include "Sequence.h"

Agent::Agent()
{
	m_isAlive = true;
	m_behaviourTree = nullptr;
	m_pGraph = nullptr;
}

Agent::~Agent()
{
}

void Agent::Update(float deltaTime)
{
	m_timer += deltaTime;

	if (m_behaviourTree != nullptr)
		m_behaviourTree->Execute(this);

	//seek to path
	if (m_path.empty() == false) {
		auto pathBegin = m_path.begin();
		if ((m_position - *(pathBegin)).SqaureMagnitude() < 1280.0f) {
			m_path.erase(pathBegin, pathBegin);
		}

		//calculate force vector
		Vector2 vecBetweenAgentTarget = m_targetPos - *m_path.begin();
		Vector2 force = vecBetweenAgentTarget.Normalized() * m_maxVelocity;

		//Add the force
		AddForce(force - m_velocity);
	}
	

	BaseEntity::Update(deltaTime);
}

/*void Agent::UpdateTarget(Vector2 a_newTargetPos)
{
	m_targetPos = a_newTargetPos;
}

void Agent::UpdateTarget(Agent * a_agent)
{
	m_targetPos = a_agent->GetPosition();
}*/

Vector2 Agent::GetTarget()
{
	return m_targetPos;
}

void Agent::SetTarget(Vector2 a_newTargetPos)
{
	m_targetPos = a_newTargetPos;
}

void Agent::SetTarget(BaseEntity * a_targetEnt)
{
	m_targetPos = a_targetEnt->GetPosition();
}

/* Agent::AddBehaviour(Behaviour* a_newBehaviour)
{
	m_behaviourTree->;
}*/

void Agent::SetBTRootNode(Behaviour * a_bTRootNode)
{
	m_behaviourTree = a_bTRootNode;
}

void Agent::SetGraphReference(Graph * a_graphReference)
{
	m_pGraph = a_graphReference;
}

Graph * Agent::GetGraphReference()
{
	return m_pGraph;
}

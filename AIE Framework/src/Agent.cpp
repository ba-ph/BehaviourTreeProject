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

	BaseEntity::Update(deltaTime);
}

void Agent::Draw(SpriteBatch * a_spritebatch)
{
	//Draw the path
	if (m_path.size() > 2)
	{
		auto currPos = m_path.begin();
		for (; currPos != m_path.end(); currPos++)
		{
			//Set nextPos to currPos + 1
			auto nextPos = currPos;
			nextPos++;

			//Check nextPos isn't end of our path
			if (nextPos == m_path.end())
				break;

			Vector2 p1 = (*currPos);
			Vector2 p2 = (*nextPos);
			a_spritebatch->setSpriteColor(1, 0.0f, 0.0f, 5.0f);
			a_spritebatch->drawLine(p1.x, p1.y, p2.x, p2.y, 2.0f);
		}
	}


	BaseEntity::Draw(a_spritebatch);
}


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

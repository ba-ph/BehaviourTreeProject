#pragma once
#include <vector>
#include "BaseEntity.h"
#include <list>
#include "Graph.h"

class Behaviour;
//Agent object with a behaviour tree
class Agent : public BaseEntity
{
public:
	Agent();
	~Agent();

	void Update(float deltaTime);
	void Draw(SpriteBatch* a_spritebatch);

	//Set/Get Current Target
	void SetTarget(Vector2 a_newTargetPos);
	void SetTarget(BaseEntity* a_targetEnt);
	Vector2 GetTarget();

	//set bt tree
	void SetBTRootNode(Behaviour* a_bTRootNode);

	//Set/Get the Graph Reference
	void SetGraphReference(Graph* a_graphReference);
	Graph* GetGraphReference();
	

	std::list<Vector2> m_path;
private:
	Vector2 m_targetPos;
	Graph* m_pGraph;

	Behaviour* m_behaviourTree;  //Root node of tree

	float m_timer;
	bool m_isAlive;

};


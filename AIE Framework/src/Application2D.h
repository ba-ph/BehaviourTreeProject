#pragma once
#include "BaseApplication.h"
#include <vector>

#include "Agent.h"
#include "Polygon.h"
#include "Input.h"
#include "Ball.h"

class Vector2;
class SpriteBatch;
class Texture;
class Font;
class EntityManager;
class BaseEntity;
class Graph;
class GraphNode;


class Application2D : public BaseApplication {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();

protected:

	SpriteBatch*	m_spriteBatch;
	Texture*		m_bgTexture;
	Font*			m_font;

private:
	EntityManager* m_entityManager;
	Input* m_input;

	Graph* pGraph;
	void CreateGraph();

	Vector2 m_mousePos;
	Transform rootTransform;
	Agent agent;
	Ball* ball;
	Texture* ballTexture;

	std::list<Vector2> path;
};
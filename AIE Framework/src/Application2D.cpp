#include "Application2D.h"
#include <GLFW/glfw3.h>

////Standard Library Includes////
#include <iostream>
#include <ctime>
#include <random>
////////////////////////////////

////Framework Includes////
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Transform.h"
#include "Vector2.h"
/////////////////////////

////Behaviour Tree////
#include "Behaviour.h"
#include "Composite.h"
#include "Sequence.h"
#include "Selector.h"
#include "WalkLeaf.h"
//////////////////////

#include "Graph.h"
#include "GraphNode.h"
#include "EntityManager.h"
#include "BaseEntity.h"


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	srand(time(NULL));
	createWindow("A.I.E Project", 1280, 920);
	setBackgroundColour(0.7f, 0.7f, 0.7f);
	m_spriteBatch = new SpriteBatch();
	ballTexture = new Texture("./bin/textures/nodeTexture.png");

	// Create a graph
	pGraph = new Graph();
	// Fill Graph
	pGraph->CreateGraph();

	//Create a hexagon
	Polygon hexagon(agent.GetTransform());
	hexagon.addVertex(Vector2(-50, 30));
	hexagon.addVertex(Vector2(0, 50));
	hexagon.addVertex(Vector2(50, 30));
	hexagon.addVertex(Vector2(50, -30));
	hexagon.addVertex(Vector2(0, -50));
	hexagon.addVertex(Vector2(-50, -30));

	//Behaviour Tree Nodes
	Sequence* rootNode = new Sequence();
	Walk* walkLeaf = new Walk();
	Sequence* pickUpBall = new Sequence();

	rootNode->AddBehaviour(walkLeaf);
	rootNode->AddBehaviour(pickUpBall);

	//Set up Ball
	ball = new Ball();
	ball->SetTexture(ballTexture);
	ball->SetPosition(Vector2(1100, 450));

	//Set up agent one
	agent.SetTexture(nullptr);
	agent.SetPolygon(hexagon);
	agent.GetTransform().SetParent(rootTransform);
	agent.GetTransform().Scale(0.5f);
	agent.SetPosition(Vector2(50.0f, 470.0f));
	agent.m_maxVelocity = 100.0f;
	agent.SetGraphReference(pGraph);
	agent.SetBTRootNode(rootNode);
	agent.SetTarget(ball);

	
	//Set up InputManager
	Input::CreateSingleton();
	m_input = Input::GetSingleton();
	getCursorPositionVec(m_mousePos);

	return true;
}

void Application2D::shutdown() {

	delete m_spriteBatch;
	delete pGraph;
	delete ballTexture;

	Input::DestroySingleton();

	destroyWindow();
}

bool Application2D::update(float deltaTime) {
	getCursorPositionVec(m_mousePos);

	agent.Update(deltaTime);
	
	rootTransform.UpdateTransforms();

	//ball->Update(deltaTime);

	//Remove Nodes
	/*if (m_input->WasKeyPressed(GLFW_KEY_Y))
		pGraph->RemoveNode(*pGraph->GetClosestNode(m_mousePos));*/

	//Toggle Graph Draw
	if (m_input->WasKeyPressed(GLFW_KEY_G))
	{
		if (pGraph->GraphEnabled)
			pGraph->GraphEnabled = false;
		else
			pGraph->GraphEnabled = true;
	}

	if (m_input->WasKeyPressed(GLFW_KEY_R))
	{
		agent.SetPosition(Vector2(50.0f, 470.0f));
	}

	// close the application if the window closes or we press escape
	if (hasWindowClosed() || isKeyPressed(GLFW_KEY_ESCAPE))
		return false;

	// the applciation closes if we return false
	return true;
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_spriteBatch->begin();

	//Calculate path                                
	/*if (pGraph->m_nodes.size() > 2)
	{
		//Calculate path
		path = pGraph->AStar(pGraph->GetNode(0), pGraph->GetNode(pGraph->m_nodes.size() -1));

		//Draw the path
		auto currPos = path.begin();
		for (; currPos != path.end(); currPos++)
		{
			//Set nextPos to currPos + 1
			auto nextPos = currPos;
			nextPos++;

			//Check nextPos isn't end of our path
			if (nextPos == path.end())
				break;

			Vector2 p1 = (*currPos);
			Vector2 p2 = (*nextPos);
			m_spriteBatch->setSpriteColor(1, 0.0f, 0.0f, 5.0f);
			m_spriteBatch->drawLine(p1.x, p1.y, p2.x, p2.y, 2.0f);
		}
	}*/

	ball->Draw(m_spriteBatch);
	agent.Draw(m_spriteBatch);
	

	if (pGraph->GraphEnabled) {
		pGraph->Draw(*m_spriteBatch);
	}

	// done drawing sprites
	m_spriteBatch->end();
}


//Has been moved into Graph Class - still here until new method tested
void Application2D::CreateGraph()
{
	const int cols = 18;
	const int rows = 13;

	GraphNode* grid[cols][rows];

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Vector2 gridPos(i*75.0f, j*75.0f);
			grid[i][j] = pGraph->AddNode(gridPos);
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (j < rows - 1) {
				pGraph->AddEdge(*grid[i][j], *grid[i][j + 1], 10);
				pGraph->AddEdge(*grid[i][j + 1], *grid[i][j], 10);
			}
			if (i < cols - 1) {
				pGraph->AddEdge(*grid[i][j], *grid[i + 1][j], 10);
				pGraph->AddEdge(*grid[i + 1][j], *grid[i][j], 10);
			}

			if (i < cols - 1 && j < rows - 1) {
				pGraph->AddEdge(*grid[i][j], *grid[i + 1][j + 1], 10);
				pGraph->AddEdge(*grid[i + 1][j + 1], *grid[i][j], 10);
			}

			if (i < cols - 1 && j < rows - 1) {
				pGraph->AddEdge(*grid[i + 1][j], *grid[i][j + 1], 10);
				pGraph->AddEdge(*grid[i][j + 1], *grid[i + 1][j], 10);
			}
		}
	}
}


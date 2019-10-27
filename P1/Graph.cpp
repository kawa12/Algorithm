#include "Graph.h"

Graph::Graph()
{
	nodeId = 0;
	isConnected = false;
	checked = false;

}

int Graph::getGraphId()
{
	return nodeId;
}

void Graph::setNodeId(int id)
{
	nodeId = id;
}

void Graph::setEdge(bool set)
{
	isConnected = set;
}

bool Graph::hasEdge()
{
	return isConnected;
}

void Graph::setVisited(bool been)
{
	checked = been;
}


bool Graph::isVisited()
{
	return checked;
}
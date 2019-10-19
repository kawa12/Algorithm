#include "Graph.h"

Graph::Graph()
{

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
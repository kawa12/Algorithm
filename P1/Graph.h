#pragma once
class Graph
{
private:
	int nodeId;
	bool isConnected;
	

public:
	Graph();
	int getGraphId();
	void setNodeId(int id);
	void setEdge(bool set);
	bool hasEdge();

	



};


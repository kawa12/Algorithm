#pragma once
class Graph
{
private:
	int nodeId;
	bool isConnected;
	bool checked;
	

public:
	Graph();
	int getGraphId();
	void setNodeId(int id);
	void setEdge(bool set);
	bool hasEdge();

	void setVisited(bool been);
	bool isVisited();


	



};


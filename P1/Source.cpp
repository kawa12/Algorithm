#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

//number of vertices for the graph
const int NODES = 15; 
//edge density in percent 1 to 100
const int DENSITY = 28; 

using namespace std;



int rollDice();
void createEdges(Graph graph[][NODES]);
void printGraph(Graph graph[][NODES]);




int main()
{
	//getting the seed for the random
	srand(time(0));
	Graph graph[NODES][NODES];
	createEdges(graph);
	printGraph(graph);


	




		return 0;
}
//-----------------------------------------------------------------------------------------
//this function sets the edges between nodes based on graph density
void createEdges(Graph graph[][NODES])
{
	int percent; 
	for (int i = 0; i < NODES; i++)
	{
		for (int j = 0; j < NODES; j++)
		{
			percent = rollDice();
			if (percent <= DENSITY)
			{
				graph[i][j].setEdge(true);
				graph[i][j].setNodeId(1);
			}
			else
			{
				graph[i][j].setEdge(false);
				graph[i][j].setNodeId(0);

			}



		}
	}
}
//-----------------------------------------------------------------------------------------
//return random number between 1 to 100 
int rollDice()
{
	int percent;
	

	percent = rand() % 100 + 1; 

	return percent; 

}
//======================================================================
//printing the graph into the console to look at the edges  0 = no edge 1 = there is a edge
void printGraph(Graph graph[][NODES])
{
	for (int i = 0; i < NODES + 1; i++)
	{
		if (i != 0)
		{
			if (i <= 9)
			{
				cout << "[0" << i << "] ";
			}
			else
			{
				cout << "[" << i << "] ";
			}
		}
		else
		{
			cout << "    ";
		}
	}
	cout << endl;
	for (int i = 0; i < NODES; i++)
	{
		if (i < 9)
		{
			cout << "[0" << i + 1 << "] ";
		}
		else
		{
			cout << "[" << i + 1 << "] ";
		}
		for (int j = 0; j < NODES; j++)
		{

			if (graph[i][j].hasEdge())
			{
				cout << graph[i][j].getGraphId() << "    ";
			}
			else
			{
				cout << graph[i][j].getGraphId() << "    ";
			}
		}
		cout << endl;
	}
}



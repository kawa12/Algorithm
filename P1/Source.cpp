#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

//number of vertices for the graph
const int NODES = 5; 
//edge density in percent 1 to 100
const int DENSITY = 45; 



using namespace std;



int rollDice();
void createEdges(Graph graph[][NODES]);
void printGraph(Graph graph[][NODES]);
void decToBinary(int n, int combination[]);
void getDomanantSet(Graph graph[][NODES], int combination[]);
void doApprox(Graph graph[][NODES], int maxSet[NODES]);
int findDomNode(Graph graph[][NODES]);
bool isNodeDisJoint(Graph graph[][NODES], int i);

struct DomNode
{
	int nodeNum;
	int edgeNum;
};



int main()
{
	//getting the seed for the random
	srand(time(0));
	int combination[NODES + 1];
	int maxSet[NODES];
	Graph graph[NODES][NODES];
	
	createEdges(graph);
	printGraph(graph);
	//getDomanantSet(graph, combination);
	doApprox(graph, maxSet);



	cout << "Estimated dominant vertices are: ";
	for (int i = 0; i < NODES; i++)
	{
		if (maxSet[i] != 0)
		{
			cout << maxSet[i] << ", ";

		}
	}
	cout << endl << endl;


	




		return 0;
}
//-----------------------------------------------------------------------------------------
//this function sets the edges between nodes based on graph density
void createEdges(Graph graph[][NODES])
{
	int percent; 
	int j;
	for (int i = 0; i < NODES; i++)
	{
		
		for (j =0; j < i; j++)
		{
			percent = rollDice();
			if (percent <= DENSITY)
			{
				graph[i][j].setEdge(true);
				graph[i][j].setNodeId(1);

				graph[j][i].setEdge(true);
				graph[j][i].setNodeId(1);
			}
			else
			{
				graph[i][j].setEdge(false);
				graph[i][j].setNodeId(0);

				graph[j][i].setEdge(false);
				graph[j][i].setNodeId(0);

			}



		}

		if (i == j)
		{
			graph[i][j].setEdge(false);
			graph[i][j].setNodeId(0);
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
//-----------------------------------------------------------------------------------------
//this function goes through different combination of graph 
void getDomanantSet(Graph graph[][NODES], int combination[])
{
	

	for (int i=0; i < NODES + 1; i++)
	{
		combination[i] = 0; 
	}
	
	

	
	//go through all the combinations until the last index of the combination is 1
	int i = 1;
	while (combination[NODES] !=1 )
	{
		decToBinary(i, combination);

		
		//cout << i << endl;
		i++;

	

	}

	


}
//-----------------------------------------------------------------------------------------------
// function to convert decimal to binary 
void decToBinary(int n, int combination[])
{
	// array to store binary number 
	//int binaryNum[NODES+1];

	// counter for binary array 
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array 
		combination[i] = n % 2;
		n = n / 2;
		i++;
	}


	
	// printing binary array in reverse order 
	//for(int j =0; j<i; j++)
		//cout << combination[j];

	//cout << endl;

}

//it finds out an estimated minimum dominated set
//==============================================================================
void doApprox(Graph graph[][NODES], int maxSet[NODES])
{
	int k = 0;
	int numberOfEdges;
	int prev = 0;
	for(int i =0; i<NODES; i++)
		maxSet[i] = 0;


	int nodeWithMaxEdges = findDomNode(graph);
	while (k<NODES)
	{
		//cout << "RECEIVED MAX NODE: " << nodeWithMaxEdges+1 << endl;
		if (isNodeDisJoint(graph, k))
		{
			maxSet[k] = k+1;
			for (int a = 0; a < NODES; a++)
				graph[k][a].setVisited(true);

			//cout << "IF " << endl;
		}
	
		else 
		{
			//cout << "ELSE" << endl;
			
			if (graph[nodeWithMaxEdges][k].hasEdge() && !graph[nodeWithMaxEdges][k].isVisited())
			{ 
				//cout << "INSIDE IF: " << endl;
				maxSet[k] = nodeWithMaxEdges + 1;
				for (int i = 0; i < NODES; i++)
				{
					graph[nodeWithMaxEdges][i].setVisited(true);
					graph[i][nodeWithMaxEdges].setVisited(true);
					for (int j = 0; j < NODES; j++)
					{
						if (graph[i][j].hasEdge() && graph[j][nodeWithMaxEdges].hasEdge())
						{
							//cout << "JAY: "<<j << endl;
							graph[i][j].setVisited(true);
							graph[j][i].setVisited(true);
						}
							
					}
					
				}
			
				
			}
			else
			{
				graph[nodeWithMaxEdges][k].setVisited(true);
				graph[k][nodeWithMaxEdges].setVisited(true);
			}
		}
		nodeWithMaxEdges = findDomNode(graph);
		//cout << "Incremented! " << endl;
		k++;
	}


	
}
//======================================================================

//this finds out what is the maximum and minimum number of edges in the graph and return the average.
int findDomNode(Graph graph[][NODES])
{

	int numberOfEdges;
	DomNode arry[NODES];

	for (int i = 0; i < NODES; i++)
	{
		
		arry[i].edgeNum = 0;
		arry[i].nodeNum = 0;

		numberOfEdges = 0;

		for (int j = 0; j < NODES; j++)
		{

			if (graph[i][j].hasEdge() && !graph[i][j].isVisited())
			{
				numberOfEdges++;

			}

		}
	
		//cout << "NODE: " << i+1 << " MAX EDGES: " << numberOfEdges << endl;
		arry[i].nodeNum = i;
		arry[i].edgeNum = numberOfEdges;
		
	}

	int max;
	int nodeNum;
	max = arry[0].edgeNum;
	nodeNum = arry[0].nodeNum;

	for (int i = 0; i < NODES; i++)
	{
		
		if (max < arry[i].edgeNum)
		{
			max = arry[i].edgeNum;
			nodeNum = arry[i].nodeNum;
		}

	}

	//cout << "MAX RETURNED NODE : " << nodeNum + 1 << " MAX EDG: "<<max << endl;
	return nodeNum;
}
//=================================================================================================
bool isNodeDisJoint(Graph graph[][NODES], int i)
{

	int counter;
	
	counter = 0;
	for (int j = 0; j < NODES; j++)
	{
		if (graph[i][j].hasEdge())
		{
			counter++;
		}
	}

	if (counter == 0)
		return true;
	else
		return false;

		
	
}
//==================================================================================================
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
			graph[i][j].setVisited(false);
		}
		cout << endl;
	}
}
//=============================================================================


#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

//number of vertices for the graph
const int NODES = 4; 
//edge density in percent 1 to 100
const int DENSITY = 60; 


using namespace std;



int rollDice();
void createEdges(Graph graph[][NODES]);
void printGraph(Graph graph[][NODES]);
void decToBinary(int n, int combination[]);
void getDomanantSet(Graph graph[][NODES], int combination[]);






int main()
{
	//getting the seed for the random
	srand(time(0));
	Graph graph[NODES][NODES];
	
	createEdges(graph);
	printGraph(graph);

	int combination[NODES + 1];
	

	getDomanantSet(graph, combination);


	




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
			}
			else
			{
				graph[i][j].setEdge(false);
				graph[i][j].setNodeId(0);

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
		for (int j = 0; j <= i; j++)
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


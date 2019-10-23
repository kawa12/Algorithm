#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

//number of vertices for the graph
const int NODES = 5; 
//edge density in percent 1 to 100
const int DENSITY = 40; 



using namespace std;



int rollDice();
void createEdges(Graph graph[][NODES]);
void printGraph(Graph graph[][NODES]);
void decToBinary(int n, int combination[]);
void getDomanantSet(Graph graph[][NODES], int combination[]);
void doApprox(Graph graph[][NODES], int maxSet[NODES]);
int getAverageNumOfEdges(Graph graph[][NODES]);





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



	cout << "Dominant vertices are: ";
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
	int avgEdge = getAverageNumOfEdges(graph);
	if (avgEdge == 0)
		{
		avgEdge = 1;
		}
	
	for (int i = 0; i < NODES; i++)
	{
		maxSet[i] = 0;
		numberOfEdges = 0;
		for (int j = 0; j < i; j++)
		{
			if (graph[i][j].hasEdge() && !graph[i][j].isVisited())
			{
				numberOfEdges++;
				//cout << i + 1 << "i " << j + 1 << "j " << endl;
				graph[i][j].setVisited(true);

				
				
					
				
				

			}
		}
		if (numberOfEdges >= avgEdge)
		{
			maxSet[k] = (i + 1);
			k++;
		}
	}
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
			graph[i][j].setVisited(false);
		}
		cout << endl;
	}
}
//=============================================================================
//this finds out what is the maximum and minimum number of edges in the graph and return the average.
int getAverageNumOfEdges(Graph graph[][NODES])
{

	int numberOfEdges;
	int arry[NODES];
	int k = 0;
	for (int i = 0; i < NODES; i++)
	{
		
		numberOfEdges = 0;

		for (int j = 0; j < i; j++)
		{
			if (graph[i][j].hasEdge() && !graph[i][j].isVisited())
			{
				numberOfEdges++;
				//cout << i + 1 << "i " << j + 1 << "j " << endl;
				//graph[i][j].setVisited(true);







			}
		}
		
		arry[k] = numberOfEdges;
		k++;
	}

	int max;
	int min;
	max = arry[0];
	min = arry[0];

	for (int i = 0; i < NODES; i++)
	{
		
		if (max < arry[i])
			max = arry[i];
		if (min > arry[i])
			min = arry[i];

	}


	//cout << "MAX " << max << endl;
	//cout << "MIN " << min << endl;

	return (min + max) / 2;
}



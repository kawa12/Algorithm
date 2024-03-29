#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include <ctime>
#include <cmath>
//number of vertices for the graph
const int NODES = 5; 
//edge density in percent 1 to 100
const int DENSITY = 46; 



using namespace std;


//it will return 1 to 100 randomlly
int rollDice();
//creates edges between vertices based on value returned by rolldice
void createEdges(Graph graph[][NODES]);
//print the graph into console 
void printGraph(Graph graph[][NODES]);
//convert decemil to backward binary
void decToBinary(int n, int combination[]);
//find the dominant set through Brute Force
void getDomanantSet(Graph graph[][NODES], int dominatedNodes[]);
//does the approxmation based on greedy algorithm 
void doApprox(Graph graph[][NODES], int maxSet[NODES]);
//finds the the vertix with most edges
int findDomNode(Graph graph[][NODES]);
//checks if the vertex is disjoint
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
	
	int maxSet[NODES];
	Graph graph[NODES][NODES];

	int dominatedNodes[NODES];
	
	createEdges(graph);
	printGraph(graph);
	
	time_t time0;
	time_t time1; 

	time(&time0);

	getDomanantSet(graph, dominatedNodes);

	time(&time1);
	
	
	int second = time1 - time0;
	int minutes = 0;
	int hours = 0;
	if (second > 60)
		{
		minutes = second / 60;
		second = fmod(second, 60);
		}

	if (minutes > 60)
		{
		hours = minutes / 60;
		minutes = fmod(minutes, 60);
		}

	cout << "Time Elapsed: " <<hours<<":"<<minutes<<":"<< second  << endl;

	doApprox(graph, maxSet);




	

	cout << "Dominant vertices are: ";
	for (int i = 0; i < NODES; i++)
	{
		if (dominatedNodes[i] != 0)
		{
			cout << dominatedNodes[i] << ", ";

		}
	}
	cout << endl << endl;


	cout << "Estimated Dominant vertices are: ";
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
void getDomanantSet(Graph graph[][NODES], int dominatedNodes[] )
{
	
	int combination[NODES + 1];
	int workArry[NODES];
	bool isDominated;
	bool dominatedSetFound = false;
	//int q = power(2, NODES);
	
		
	

	for (int t=0; t < NODES+1; t++)
	{
		combination[t] = 0;
		if (t < NODES)
		{
			workArry[t] =0;
			*(dominatedNodes+t) =0;
		}
	
		
	}
	
	//cout << binaryToDec(workArry) << endl;
	
	//go through all the combinations until the last index of the combination is 1
	int i = 1;

	int add = 0;
	while (combination[NODES] !=1)
	{
		decToBinary(i, combination);
		for (int d = 0; d < NODES; d++)
			{
			workArry[d] = combination[d];
			}

		for (int a = 0; a < NODES; a++)
		{
			if (workArry[a] == 1)
			{
				
				for (int v = 0; v<NODES; v++)
				{
					
					if (graph[a][v].hasEdge())
					{
						if (workArry[v] == 0)
						{
							workArry[v] = 2;
						
						}


					}
					
		
				}
				

				isDominated = true;
				for (int y = 0; y < NODES; y++)
				{
					//cout << workArry[y];
					if (workArry[y] == 0)
						isDominated = false;
				}
				//cout << endl;

				if (isDominated && !dominatedSetFound)
				{
					//cout << "Found Dominated Set" << endl;
					for (int r = 0; r < NODES; r++)
					{
						if (workArry[r] == 1)
						{
						dominatedNodes[add] = r + 1;
						add++;
						//cout << 1+r <<", ";
						
						}

					
					}
					cout << endl;
					dominatedSetFound = true;
					
					
					
				}
			}
			//if (dominatedSetFound)
			//	break;
		}
		

		i++;
	

	}
	



}
//-----------------------------------------------------------------------------------------------
// function to convert decimal to binary 
void decToBinary(int n, int combination[])
{

	int i = 0;
	while (n > 0) {

		// storing remainder in binary array 
		combination[i] = n % 2;
		n = n / 2;
		i++;
	}


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

	for (int l = 0; l < NODES; l++)
	{
		if (isNodeDisJoint(graph, l))
		{
			maxSet[prev] = l + 1;
			prev++;
		}
	}
	int nodeWithMaxEdges = findDomNode(graph);
	while (k <(NODES*NODES))
	{
		//cout << "RECEIVED MAX NODE: " << nodeWithMaxEdges+1 << endl;
		
	
		if (graph[nodeWithMaxEdges][k].hasEdge())
		{ 
				//cout << "INSIDE IF: " << endl;
			maxSet[prev] = nodeWithMaxEdges + 1;
			for (int i = 0; i < NODES; i++)
			{

				graph[nodeWithMaxEdges][i].setEdge(false);
				graph[i][nodeWithMaxEdges].setEdge(false);
				
			/*	for (int m = 0; m < NODES; m++)
				{
					if (graph[i][m].hasEdge())
					{
						graph[i][m].setEdge(false);
						graph[m][i].setEdge(false);
					}
				}*/
				
				
			}
			//printGraph(graph);
			nodeWithMaxEdges = findDomNode(graph);
			prev++;
			
		}	
	
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

			if (graph[i][j].hasEdge())
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
				cout << 1 << "    ";
			}
			else
			{
				cout << 0 << "    ";
			}
			graph[i][j].setVisited(false);
		}
		cout << endl;
	}
}

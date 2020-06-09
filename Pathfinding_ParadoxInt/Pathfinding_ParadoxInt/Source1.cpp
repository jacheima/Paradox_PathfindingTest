#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <chrono>
#include <math.h>
#include <string>

#define INF 10000000

using namespace std;
using namespace std::chrono;


//the number of node in the map
int numberOfNodes;

//pointer to the adjacent nodes list
list<pair<int, int>>* adjacentNodes;

//our map constructor
void Map(int nodes);

//The function to add an edge and cost
void addEdge(int nodeA, int nodeB, int cost);

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, int pOutBufferSize);

void initializeMap(const unsigned char* pMap, int pOutBufferSize, const int nMapWidth,
	const int nMapHeight, int target);

//Constructor for the number of nodes
void Map(int nodes)
{
	//set up the nodes
	numberOfNodes = nodes;

	//create a new list to hold the adjacent nodes
	adjacentNodes = new list<pair<int, int>>[numberOfNodes];
}

void initializeMap(const unsigned char* pMap, int pOutBufferSize, const int nMapWidth,
	const int nMapHeight, int target)
{
	int currentRow = 0;
	int cost = 1;

	for (int i = 0; i < nMapWidth * nMapHeight; i++)
	{
		//get the right edge pieces
		if (i == (nMapWidth * currentRow) - (1 - nMapWidth))
		{
			if ((int)pMap[i] == (int)1)
			{
				if (i == nMapWidth - 1) //bottom right corner
				{
					if ((int)pMap[i + nMapWidth] == (int)1)
					{
						//connect to the node above
						addEdge(i, i + nMapWidth, cost);
					}


					if ((int)pMap[i - 1] == (int)1)
					{
						//connect to the node to the left
						addEdge(i, i - 1, cost);
					}



				}
				else if (i == (nMapWidth * nMapHeight) - 1) //top right corner
				{
					if ((int)pMap[i - nMapWidth] == (int)1)
					{
						//connect to the node below
						addEdge(i, i - nMapWidth, cost);

					}


					if ((int)pMap[i - 1] == (int)1)
					{

						//connect to the node to the left
						addEdge(i, i - 1, cost);
					}

				}
				else //right edge piece between corners
				{
					if ((int)pMap[i - nMapWidth] == (int)1)
					{
						//connect to the node below
						addEdge(i, i - nMapWidth, cost);
					}


					if ((int)pMap[i + nMapWidth] == (int)1)
					{
						//connect to the node above
						addEdge(i, i + nMapWidth, cost);
					}


					if ((int)pMap[i - 1] == (int)1)
					{
						//connect to the node to the left
						addEdge(i, i - 1, cost);
					}


				}
			}

			currentRow++;
		}
		//get the left edge pieces
		else if (i == nMapWidth * currentRow)
		{
			if ((int)pMap[i] == (int)1)
			{
				if (i == 0) // bottom left corner
				{
					if ((int)pMap[i + nMapWidth] == (int)1)
					{
						//connect to the node above
						addEdge(i, i + nMapWidth, cost);
					}


					if ((int)pMap[i + 1] == (int)1)
					{
						//connect to the node to the right
						addEdge(i, i + 1, cost);
					}


				}

				if (i == (nMapWidth * (nMapHeight - 1))) //top left corner
				{
					//if the node to our right exists
					if ((int)pMap[i + 1] == (int)1)
					{
						//connect to the node to the right
						addEdge(i, i + 1, cost);

					}


					//if the node below us exists
					if ((int)pMap[i - nMapWidth] == (int)1)
					{
						//connect to the node below
						addEdge(i, i - nMapWidth, cost);
					}

				}
				else//the left edge pieces between the corners
				{
					if ((int)pMap[i + nMapWidth] == (int)1)
					{
						//connect to the node above
						addEdge(i, i + nMapWidth, cost);

					}


					if ((int)pMap[i - nMapWidth] == (int)1)
					{
						//connect to the node below
						addEdge(i, i - nMapWidth, cost);
					}


					if ((int)pMap[i + 1] == (int)1)
					{
						//connect to the node to the right
						addEdge(i, i + 1, cost);
					}


				}
			}
		}
		//get the bottom edge nodes
		else if (i > 0 && i < (nMapWidth - 1))
		{
			if ((int)pMap[i] == (int)1)
			{
				if ((int)pMap[i - 1] == (int)1)
				{
					//connect to the node to the left
					addEdge(i, i - 1, cost);
				}


				if ((int)pMap[i + 1] == (int)1)
				{
					//connect to the node to the right
					addEdge(i, i + 1, cost);
				}


				if ((int)pMap[i + nMapWidth] == (int)1)
				{
					//connect to the node above
					addEdge(i, i + nMapWidth, cost);

				}

			}
		}
		//get the top edge
		else if (i > ((nMapWidth * nMapHeight) - 1) - (nMapWidth - 1) && i < ((nMapWidth * nMapHeight) - 1))
		{
			if ((int)pMap[i] == (int)1)
			{
				if ((int)pMap[i - 1] == (int)1)
				{
					//connect to the node to the left
					addEdge(i, i - 1, cost);
				}


				if ((int)pMap[i + 1] == (int)1)
				{
					//connect to the node to the right
					addEdge(i, i + 1, cost);
				}


				if ((int)pMap[i - nMapWidth] == (int)1)
				{
					//connect to the node below
					addEdge(i, i - nMapWidth, cost);
				}



			}
		}
		else
		{
			if ((int)pMap[i] == (int)1)
			{
				if ((int)pMap[i + 1] == (int)1)
				{
					//connect to the node to the right
					addEdge(i, i + 1, cost);
				}

				if ((int)pMap[i - 1] == (int)1)
				{
					//connect to the node to the left
					addEdge(i, i - 1, cost);
				}


				if ((int)pMap[i + nMapWidth] == (int)1)
				{
					//connect to the node above
					addEdge(i, i + nMapWidth, cost);
				}


				if ((int)pMap[i - nMapWidth] == (int)1)
				{
					//connect to the node below
					addEdge(i, i - nMapWidth, cost);
				}
			}
		}

	}

}


void addEdge(int nodeA, int nodeB, int cost)
{
	//at the cost to the nodes list
	adjacentNodes[nodeA].push_back(make_pair(nodeB, cost));
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer,
	int pOutBufferSize)
{
	Map(nMapHeight * nMapWidth);

	//get the points node number
	int start = nStartX + (nStartY * nMapWidth);
	int target = nTargetX + (nTargetY * nMapWidth);

	initializeMap(pMap, pOutBufferSize, nMapWidth, nMapHeight, target);

	if (start == target)
	{
		return 0;
	}
	else if ((int)pMap[target] == (int)0 || (int)pMap[start] == (int)0)
	{
		return -1;
	}
	else
	{
		//create a set to store the nodes
		set<pair<int, int>> extractSet;

		//store all the distances between nodes
		//all paths initialized to a very large number
		vector<int> distances(numberOfNodes, INF);

		vector<int>parent(numberOfNodes, 0);

		//insert the start node and set its distance to 0
		extractSet.insert(make_pair(0, start));
		distances[start] = 0;

		while (!extractSet.empty())
		{
			pair<int, int> temp = *(extractSet.begin());
			extractSet.erase(extractSet.begin());

			//get the node number 
			int currentNode = temp.second;

			for (auto i = adjacentNodes[currentNode].begin(); i != adjacentNodes[currentNode].end(); i++)
			{
				int num = 0;

				//get the node and its cost
				int node = (*i).first;
				int cost = (*i).second;

				if (distances[node] > distances[currentNode] + cost)
				{
					if (distances[node] != INF)
					{
						extractSet.erase(extractSet.find(make_pair(distances[node], node)));
					}

					//update the distance
					distances[node] = distances[currentNode] + cost;
					extractSet.insert(make_pair(distances[node], node));

					if ((fabs(nTargetX - nStartX) + fabs(nTargetY - nStartY)) < pOutBufferSize)
					{
						pOutBuffer[distances[node] - 1] = node;
					}
				}

				if (node == target)
				{
					return distances[node];
				}
			}
		}
	}

	return -1;
}

void GenerateTest()
{
	int mapWidth;
	int mapHeight;
	int outBufferSize;
	int mapArrayLength;


	for (int i = 0; i < 1000; i++)
	{
		mapWidth = rand() % 500 + 1;
		mapHeight = rand() % 500 + 1;
		int outBufferSize = rand() % 500;
		int mapArrayLength = mapWidth * mapHeight;




	}
}



int main(void)
{

	auto start = high_resolution_clock::now();

	unsigned char pMap[] = {
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1
	};
	int pOutBuffer[10];

	

	int shortestDistance = FindPath(0, 0, 1, 1, pMap, 3, 3, pOutBuffer, 10);

	

	cout << shortestDistance << endl;
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << pOutBuffer[i] << endl;
	}

	auto stop = high_resolution_clock::now();
	auto timeTaken = duration_cast<microseconds>(stop - start);

	cout << "The program took ";
	cout << timeTaken.count() << " microseconds";
}
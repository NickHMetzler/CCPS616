/* 
# lab2.cpp
# Yiran Zhu and Nicolas Metzler
# Student ID's: 500571811 and 501050712
# Lab #1 - Divide and Conquer
# CPS 616 Section BA0
# Instructor: A. Ufkes
# Purpose: C++ program that performs large integer multiplication.
#
# I hereby attest that I am the sole owner and author of this code (except where referenced) and that to the best of my knowledge, this code has not infringed on anyone’s copyright. 
# Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;
using namespace std::chrono; // Namespace for fancy ms timing

void printGraph(int** graph, int V);
void fillRandGraph(int **graph, int V, int E, int maxWeight = 9);
bool validateST(int** st, int** graph, int V);


// struct for coordinates
struct  vertex{
    int x;
    int y;
};

void printArr(int *input, int size){
  
 
    // loop through the array elements
    for (int i = 0; i < 6*2; i++) {
        std::cout << input[i] << ' ';
    }
}

bool searchCoords(int *arr, int size, int x, int y){
  bool found = false;
  
  for(int i = 0; i <= size - 2; i += 2){
    if(x == arr[i] && y == arr[i+1]){
      found = true;
      break;
    }
  } 
  return found;
}



void minimumSpanningTree(int **graph, int **mst, int V)
{
  int nodeCoords[V * 2], coordInd = 0;
  
  
  for(int i = 0; i <= V - 1; i++){
    // Run through each Row
    int min = 10000, minRow = 0, minCol = 0;
    
    for(int j = 0; j <= V - 1; j++){
      // Run through each Column
      if(graph[i][j] < min && graph[i][j] != 0){
        if(searchCoords(nodeCoords, V*2, i, j) == true || searchCoords(nodeCoords, V*2, j, i) == true){
          printf("\nFound Dupe %d at [%d]\n", graph[i][j], i, j);
            mst[i][j] = graph[i][j];
            nodeCoords[coordInd] = i;
        nodeCoords[coordInd + 1] = j;
        coordInd++;
        }
        else{
          min = graph[i][j];
          minCol = j;
          printf("New min found %d\n", min);
        }
      
      }

      if((j == V - 1) && min != 0 && min != 69420){
        mst[i][minCol] = min;
        nodeCoords[coordInd] = i;
        nodeCoords[coordInd + 1] = minCol;
        coordInd++;
        printArr(nodeCoords, V * 2);
        printf("\nThis is the min: %d\n\n", min);
      }
      
      
    }
  }
}

/*void minimumSpanningTree(int **graph, int **mst, int V)
{
	/**************** YOUR CODE HERE! **************
	// Parameter V = number of vertices = size of adjacency matrix
	// You may assume parameters graph and mst are properly
	// allocated 2D arrays of size [V][V]
	// You need not allocate or deallocate them in this function

  // Start by searching the MST for nodes 1
  //Loop through the entire MST
  int min = 69420, minRow = 0, minCol = 0, row = 0, col = 0, hitInd = 0, coordInd = 0;
  int noNode[V], nodeCoords[V * 2];
  
  //printf("\nCheck 6 %d\n\n", *graph[7]);
  
  for(int i = 0; i <= V - 1; i++){
    // Run through each row
    //printf("thru I:::");
    
    for(int j = 0; j <= V - 1; j++){
      
      if(graph[i][j] < min && graph[i][j] != 0){ // && (searchFor(noNode, V, j) == false)
        if(searchCoords(nodeCoords, V*2, i, j) == true || searchCoords(nodeCoords, V*2, j, i) == true){
          printf("\nFound Dupe");
          break;
        }
        else{
          min = graph[i][j];
        minRow = row;
        minCol = col;
        printf("\nHIT %d", min);
        }
        
      }

      // Done iterating through the row
      if((j == V - 1) && min != 0 && min != 69420){
        mst[i][minCol] = min;
        mst[minCol][i] = min;
        noNode[hitInd] = i;
        nodeCoords[coordInd] = i;
        nodeCoords[coordInd + 1] = minCol;
        coordInd++;
        hitInd++;
        //printf("\nThis is the min: %d\n\n", min);
      }
      col++;
    }
    printf("\nRow Set\n");
    col = 0;
    min = 69420;
    row++;
    }
}*/


int main()
{
	char name[] = "Nicolas Metzler and Yiran Zhu";

	srand((int)time(NULL));
	printf("\nCCPS616 - Lab 3 - %s\n\n", name);

	/*******************************************************************/
	/* First, test algorithm correctness on simple example from classn */
	/* You should create your own additional examples here!            */
	/*******************************************************************/
	{
		const int V = 6;
		int gNums[] = { 0,1,0,0,5,0, 1,0,8,0,2,0, 0,8,0,1,0,0, 0,0,1,0,4,2, 5,2,0,4,0,0, 0,0,0,2,0,0 };
		int gMST[] = { 0,1,0,0,0,0, 1,0,0,0,2,0, 0,0,0,1,0,0, 0,0,1,0,4,2, 0,2,0,4,0,0, 0,0,0,2,0,0 };

		// 2D arrays in C/C++ are tedious. This is just creating a 2D array capable of double
		// indexing and setting up pointers to the interior of the 1D arrays above. This way
		// is more technical, but provides good cache locality because everything is contiguous.
		int **g = new int*[V];
		g[0] = gNums;
		for (int i = 1; i < V; i++)
			g[i] = g[i - 1] + V;

		int **mst = new int*[V];
		mst[0] = gMST;
		for (int i = 1; i < V; i++)
			mst[i] = mst[i - 1] + V;

		int **yourMST = new int*[V];
		yourMST[0] = new int[V*V](); // The () is a C++ trick for initializing elements to 0
		for (int i = 1; i < V; i++)
			yourMST[i] = yourMST[i - 1] + V;

		cout << "Testing simple example from the description... " << endl;
		printGraph(g, V);
		cout << endl << "MST should be:" << endl;
		printGraph(mst, V);

		minimumSpanningTree(g, yourMST, V);

		cout << endl << "You said:" << endl;
		printGraph(yourMST, V);
		cout << endl;

    printGraph(g, V);
		//assert(validateST(yourMST, g, V));

		delete[] yourMST[0];
		delete[] yourMST;
	}

	// Number of vertexes in large random graph
	int V = 2000;

	// Create a contiguous 2D array that still allows double indexing. Good for cache locality!
	int** graph = new int*[V];
	graph[0] = new int[V*V](); // The () is a C++ trick for initializing elements to 0
	for (int i = 1; i < V; i++)
		graph[i] = graph[i - 1] + V;

	// Create similar array for storing MST
	int** graph_mst = new int*[V];
	graph_mst[0] = new int[V*V](); // The () is a C++ trick for initializing elements to 0
	for (int i = 1; i < V; i++)
		graph_mst[i] = graph_mst[i - 1] + V;

	/*****************************************************************/
	/* Time randomized test on large, SPARSE graph where |E| = 3*|V| */
	/*****************************************************************/
	{
		int E = 4 * V;
		fillRandGraph(graph, V, E);

		cout << "Testing on random SPARSE graph (E = " << E << ")" << endl;

		auto begin = high_resolution_clock::now();
		//minimumSpanningTree(graph, graph_mst, V);
		auto dur = high_resolution_clock::now() - begin;
		int msTime = (int)duration_cast<milliseconds>(dur).count();

		// Un-comment this assertion to validate your spanning tree
		//assert(validateST(graph_mst, graph, V));
		cout << "  Done in " << msTime << "ms" << endl << endl;
	}

	/**************************************************************************/
	/* Time randomized test on large, DENSE graph where |E| = |V|*(|V|-1) / 3 */
	/**************************************************************************/
	{
		int E = V*(V - 1) / 4;
		fillRandGraph(graph, V, E);

		cout << "Testing on random DENSE graph (E = " << E << ")" << endl;

		auto begin = high_resolution_clock::now();
		//minimumSpanningTree(graph, graph_mst, V);
		auto dur = high_resolution_clock::now() - begin;
		int msTime = (int)duration_cast<milliseconds>(dur).count();

		// Un-comment this assertion to validate your spanning tree
		//assert(validateST(graph_mst, graph, V));
		cout << "  Done in " << msTime << "ms" << endl << endl;
	}

	// Deallocate graphs
	delete[] graph[0];
	delete[] graph;

	delete[] graph_mst[0];
	delete[] graph_mst;

	printf("\n");
	//system("pause");
}



// Generate a random connected graph in the form of an adjacency matrix
void fillRandGraph(int **graph, int V, int E, int maxWeight)
{
	int max_edges = V*(V - 1) / 2;

	assert(E >= V - 1);	    // Minimum number of edges while still being connected
	assert(E <= max_edges); // Maximum number of edges without duplicate edges

							// Set everything to zero, just in case it isn't already. This is better done 
							// with memset(), but doing that correctly depends on how graph is allocated.
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			graph[i][j] = 0;

	// initialize vectors for visited and unvisited vertexes
	vector<int> visited, unvisited;
	// To start, everything is unvisited (vertex ID 0 to V-1)
	for (int i = 0; i < V; i++)
		unvisited.push_back(i);
	// Shuffle vector of unvisited vertexes
	std::random_shuffle(unvisited.begin(), unvisited.end());
	// Add last element to visited, remove from unvisited
	visited.push_back(unvisited.back());
	unvisited.pop_back();

	// Randomly connect unvisited vertexes until none remain
	// This results in a spanning tree (V-1 edges)
	for (int uv : unvisited) {
		int vv = visited[rand() % visited.size()];
		graph[vv][uv] = graph[uv][vv] = rand() % maxWeight + 1;
		visited.push_back(uv);
	}
	assert(visited.size() == V);

	// Create vector of vertex pairs without edges. This seems like a 
	// hacky and costly way of doing this, but meh...
	vector<pair<int, int>> non_edges;
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			if (graph[i][j] == 0)
				non_edges.push_back(pair<int, int>(i, j));
	assert(non_edges.size() + (V - 1) == max_edges);

	// Insert remaining E-(V-1) edges, shuffling non_edges ensures randomness
	int edgesToAdd = E - (V - 1);
	if (edgesToAdd > 0) {
		std::random_shuffle(non_edges.begin(), non_edges.end());
		for (int i = 0; i < edgesToAdd; i++) {
			int v1 = non_edges[i].first;
			int v2 = non_edges[i].second;
			int wgt = rand() % maxWeight + 1;
			graph[v1][v2] = graph[v2][v1] = wgt;
		}
	}

	// Sanity check #1. Ensure adjacency matrix is symmetrical
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			assert(graph[i][j] == graph[j][i]);

	// Sanity check #2. Count non-zero elements in graph, should == E 
	int nEdge = 0;
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			nEdge = graph[i][j] != 0 ? nEdge + 1 : nEdge;
	assert(nEdge == E);
}

// Simple function for printing an adjacency matrix
void printGraph(int** graph, int V)
{
	printf("V = %d\n", V);
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++)
			printf("%-3d", graph[i][j]);
		printf("\n");
	}
}

// Function for verifying that st is a spanning tree for graph
// Does NOT determine if the spanning tree is minimum
// Just checks for the existence and right number of edges
bool containsCycle(int** graph, int V);
bool cycleUtil(int** graph, int V, int vert, int *visited, int parent);
bool validateST(int** st, int** graph, int V)
{
	// Count edges, should = V-1. If not, st cannot be a spanning tree
	int e = 0;
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			e = st[i][j] != 0 ? e + 1 : e;
	if (e != V - 1)
		return false;

	// Ensure edges present in st are actually in the original graph
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			if (st[i][j] != 0 && graph[i][j] != st[i][j])
				return false;

	// Check for cycle in spanning tree
	if (containsCycle(st, V))
		return false;

	// If no cycle, we're all set
	return true;
}

bool containsCycle(int** graph, int V)
{
	int *visited = new int[V]();
	return cycleUtil(graph, V, 0, visited, -1);
}

bool cycleUtil(int** graph, int V, int vert, int *visited, int parent)
{
	visited[vert] = 1;

	for (int j = 0; j < V; j++) {
		if (graph[vert][j] != 0)
		{
			if (!visited[j]) {
				if (cycleUtil(graph, V, j, visited, vert))
					return true;
			}
			else if (j != parent)
				return true;
		}
	}
	return false;
}
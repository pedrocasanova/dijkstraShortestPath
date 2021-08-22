#include <iostream>
#include <iomanip>
#include <random>

using namespace std;
class graph
{
  private: 
    float lowerLimit = 1, upperLimit = 10;
    int adjSize = 0;  
    float ** adjMatrix;
  public:
    float inf;
    graph(int size, float lowerLimit = 1, float upperLimit = 10, float density = 0.5)
    {
        std::cout << std::setprecision(2) << std::fixed;
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_real_distribution<> distr(lowerLimit, upperLimit); // define the range
        std::uniform_real_distribution<> prob(0, 1); // define probability range for edge placement
        float probVal;
        inf = upperLimit + 500;
        adjSize = size;
        adjMatrix = new float*[adjSize];
        for (int i = 0; i < adjSize; ++i)
        {
            adjMatrix[i] = new float[adjSize];
        }
        // populate the graph according to the correct density
        for (int i = 0; i < adjSize; ++i)
        {
            for (int j = 0; j < adjSize; ++j)
            {
                probVal = prob(gen);
                if (i == j) adjMatrix[i][j] = 0;
                if ((i < j) && (probVal > density))  adjMatrix[i][j] = distr(gen);  // generate random edge
                else if ((i < j) && probVal < density) adjMatrix[i][j] = 0; // generate 0 edge
                else adjMatrix[i][j] = adjMatrix[j][i];
            }
        }
    }
    int getNumberNodes(void)
    {
        return adjSize;
    }
    // returns number of edges within a graph
    int getNumberEdges(void)
    {
        int numEdges = 0;
        for(int i = 0; i < adjSize; ++i)
        {
            for (int j = 0; j < adjSize; ++j)
            {
                if (adjMatrix[i][j] != 0) numEdges++;
            }
        }
        return numEdges/2;  // divides by 2 because graph is undirected
    }
    // checks if nodes U and W are adjacent
    int isAdjacent(int nodeU, int nodeW)
    {
        if ((nodeU >= adjSize) || (nodeW >= adjSize) || (nodeU < 0) || (nodeW < 0)) 
        {
            cout << "Invalid parameters for isAdjacent!" << endl;
            return -1;  // invalid parameters
        } 
        else if (adjMatrix[nodeU][nodeW] != 0) return 1;    // a non-zero value here means that there is an edge
        else return 0;
    }
    // lists all neighboors of node U
    void neighbors(int nodeU)
    {
        if ((nodeU >= adjSize)  || (nodeU < 0)) 
        {
            cout << "Invalid parameters for isAdjacent!" << endl;
            return;  // invalid parameters
        } 
        for(int i = 0; i < adjSize; ++i)
        {
            if (adjMatrix[nodeU][i] != 0) cout << i << " is a neighbor of " << nodeU << endl;
        }
    }
    // sets value between to edges to 0 (ie: no edge)
    void deleteEdge(int nodeU, int nodeW)
    {
        if ((nodeU >= adjSize) || (nodeW >= adjSize) || (nodeU < 0) || (nodeW < 0)) 
        {
            cout << "Invalid parameters for isAdjacent!" << endl;
            return;  // invalid parameters
        } 
        adjMatrix[nodeU][nodeW] = adjMatrix[nodeW][nodeU] = 0;
    }
    // deletes all edges of the graph
    void clearGraph()
    {
        for (int i = 0; i < adjSize; ++i)
        {
            for (int j = 0; j < adjSize; ++j)
            {
                deleteEdge(i,j);
            }    
        }
        return; 
    }
    // return value between edges
    float getEdgeValue(int nodeU, int nodeW)
    {
        if ((nodeU >= adjSize) || (nodeW >= adjSize) || (nodeU < 0) || (nodeW < 0)) 
        {
            cout << "Invalid parameters for getEdgeValue!" << endl;
            return -1;  // invalid parameters
        } 
        return adjMatrix[nodeU][nodeW];
    }
    // set to edgeWeight the value between nodes U and W 
    void setEdgeValue(int nodeU, int nodeW, float edgeWeight)
    {
        if ((nodeU >= adjSize) || (nodeW >= adjSize) || (nodeU < 0) || (nodeW < 0)) 
        {
            cout << "Invalid parameters for setEdgeValue!" << endl;
            return;  // invalid parameters
        } 
        adjMatrix[nodeU][nodeW] = adjMatrix[nodeW][nodeU] = edgeWeight; // set adjacency matrix values to desired ones
    }
    // calculates shortest path between nodes
    float shortestPath()
    {
        // do dijkstra's algorithm for each node and compute avg shortest path
        float avgShortestDistance = 0, shortestDistanceFromX[adjSize];
        float min = inf;
        bool visited[adjSize], allVisitedFlag = false;
        int previousNode[adjSize];
        int i = 0, prev;  // doing this for node 0 (A) -> then add for loop with all nodes
        int next = 0;
        // initialize the shortest distances from X node
        for (int j = 0; j < adjSize; ++j)
        {
            if (j == i) shortestDistanceFromX[j] = 0;   // no loops
            else shortestDistanceFromX[j] = inf;
            visited[j] = false;
            previousNode[j] = adjSize + 399;
        }
        // 0th iteration
        for (int k = 0; k < adjSize; k++)
        {
            // shortest distance of a node to itself is zero (again, no loops)
            if (k == i) shortestDistanceFromX[k] = 0;
            // if edge exists and is shorter than current distance then it is the new shortest distance
            if (adjMatrix[i][k] < shortestDistanceFromX[k] && adjMatrix[i][k] >= lowerLimit)
            {
                // update shortest distance
                shortestDistanceFromX[k] = adjMatrix[i][k];
                // cout << "i,k: " << i << " " << k << "short: " << shortestDistanceFromX[k] << endl;
                // update previous vertex
                previousNode[k] = i;
            }
        }
        visited[i] = true;
        // visit the unvisited node with the smallest shortest distance to start node
        for (int m = 0; m < adjSize; m++)
        {
            if((shortestDistanceFromX[m] < min) && (visited[m] == false))
            {
                next = m;   // select next node to visit
                min = shortestDistanceFromX[m]; // update minimum value
            }
        }
        // check if all nodes have been visited yet
        allVisitedFlag = true;
        for (int m = 0; m < adjSize; ++m)
        {
            if (visited[m] == false) allVisitedFlag = false;
        }
        while (allVisitedFlag == false)
        {
            // nth iteration
            prev = i;
            i = next;
            for (int k = 0; k < adjSize; k++)
            {
                // if edge exists and is shorter than current distance then it is the new shortest distance
                if (adjMatrix[i][k] + shortestDistanceFromX[i] < shortestDistanceFromX[k] && adjMatrix[i][k] >= lowerLimit && adjMatrix[i][k] < upperLimit && visited[k] == false)
                {
                    // update shortest distance
                    shortestDistanceFromX[k] = adjMatrix[i][k] + + shortestDistanceFromX[i];
                    // update previous node
                    previousNode[k] = i;
                }
            }
            visited[i] = true;
            min = inf;
            // calculate next node to be visited
            for (int m = 0; m < adjSize; m++)
            {
                if((shortestDistanceFromX[m] < min) && (visited[m] == false))
                {
                    next = m;
                    min = shortestDistanceFromX[m];
                }
            }
            // check if all nodes have been visited yet
            allVisitedFlag = true;
            for (int m = 0; m < adjSize; ++m)
            {
                if (visited[m] == false) allVisitedFlag = false;
            }
        }
        for (int j = 0; j < adjSize; ++j)
        {
            cout << "The shortest distance from node 0 to node " << j << " is: "<< shortestDistanceFromX[j] << endl;
            cout << "The previous node from node " << j << " to node 0 is: ";
            if (previousNode[j] > upperLimit) cout << "Non-existent" << endl;   // plausibility check
            else cout << previousNode[j] << endl; 
        }
        // prints info and average shortest path
        float avgShortestPath = 0, counter = 0;
        for (int i = 0; i < adjSize; ++i)
        {
            if (shortestDistanceFromX[i] < lowerLimit || shortestDistanceFromX[i] > upperLimit) {}   // check for valid value
            else 
            {
                avgShortestPath += shortestDistanceFromX[i];
                counter++;
            }
        }
        cout << "Average shortest path is: " << avgShortestPath/counter << endl;
        return avgShortestPath/counter;
    }
};

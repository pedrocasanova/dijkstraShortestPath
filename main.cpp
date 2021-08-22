
#include "graph.h"
using namespace std;

int main()
{
    graph mySparseGraph = graph(50, 1, 10, 0.2);
    graph myDenseGraph = graph(50, 1, 10, 0.4);
    graph myExampleGraph = graph(5, 1, 10, 0.5);
    
    
    mySparseGraph.shortestPath();
    myDenseGraph.shortestPath();
    cout << "Begin demonstration:" << endl; 
    myExampleGraph.clearGraph();
    myExampleGraph.setEdgeValue(0, 1, 6);
    myExampleGraph.setEdgeValue(0, 3, 1);
    myExampleGraph.setEdgeValue(1, 2, 5);
    myExampleGraph.setEdgeValue(1, 3, 2);
    myExampleGraph.setEdgeValue(1, 4, 2);
    myExampleGraph.setEdgeValue(2, 4, 5);
    myExampleGraph.setEdgeValue(3, 4, 1);
    cout << "Modified graph has " << myExampleGraph.getNumberEdges() << " edges and "
                                  << myExampleGraph.getNumberNodes() << " nodes" << endl;
    cout << "Nodes 0 and 1 adjacency: " << myExampleGraph.isAdjacent(0, 1) << endl;
    myExampleGraph.neighbors(2);
    myExampleGraph.shortestPath();
    return 0;
}
    
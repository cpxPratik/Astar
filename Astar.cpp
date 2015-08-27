#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct edge {
    char* start;
    char* end;
    int pathCost;
   // int directPath;
};
class graph {
private:
    int** path;
    int** directPath;
    char** names;
    char** shortNames;
    int noOfNodes;
public:
    graph(int noOfNodes, char* names[][2]);
    ~graph();
    bool isConnected(int, int);
    void addEdge(int n1, int n2, int pathcost, int directPathCost);
    void addEdge(int noOfEdges, edge e[]);
    void listNodes();
    void setDirectPath(char* start, char* end, int directPathCost);
    void findShortestpath(char* start, char* goal);
};
void graph::listNodes() {
    for(int i = 0; i < noOfNodes; i++){
        cout << i << "  " << names[i] << " - " << shortNames[i] << endl;
    }

}
graph::graph(int no, char* namesArg[][2] ) {
    noOfNodes = no;
    path = new int*[no];
    directPath = new int*[no];
    names = new char*[no];
    shortNames = new char*[no];
    for(int i = 0; i < no; i++){
        path[i] = new int[no];
        directPath[i] = new int[no];
        *(names+i) = namesArg[i][0];
        *(shortNames+i) = namesArg[i][1];
        for(int j = 0; j < no; j++)
            path[i][j] = directPath[i][j] = -1;
    }
}
graph::~graph() {
    for(int i = 0; i<noOfNodes; i++) {
        delete[] names[i];
        delete[] shortNames[i];
        delete[] path[i];
        delete[] directPath[i];
    }
    delete names;
    delete shortNames;
    delete path;
    delete directPath;
}
bool graph::isConnected(int node1, int node2) {
    return (path[node1][node2] >= 0);
}
void graph::addEdge(int n1, int n2, int pathcost, int directPathCost) {
    path[n1-1][n2-1] = path[n2-1][n1-1] = pathcost;
    directPath[n1-1][n2-1] = directPath[n2-1][n1-1] = directPathCost;
}
void graph::setDirectPath(char* start, char* end, int directPathCost) {
    int i,j;
    for(i=0; i<noOfNodes; i++) {
        if( strcmpi( shortNames[i], end) == 0)
            break;
    }
    for(j=0; j<noOfNodes; j++) {
        if( strcmpi( shortNames[j], end) == 0)
            break;
    }
    directPath[i][j] = directPath[j][i] = directPathCost;
}
void graph::findShortestpath(char* start, char* goal) {
	int i,j;
    for(i=0; i<noOfNodes; i++) {
        if( strcmpi( shortNames[i], end) == 0)
            break;
    }
    for(j=0; j<noOfNodes; j++) {
        if( strcmpi( shortNames[j], end) == 0)
            break;
    }
    int startNode = i, goalNode = j;
	int leastCostSoFar = 0;
	int pathToGoal[noOfNodes];
	int top = -1;
	pathToGoal[++top] = startNode;
	int selectedNode = startNode;
	int supposedSelectedNode;
	int supposedleastCost = -1 , tempLeastCost; 
	while(selectedNode != goalNode) {
		for(i = 0; i < noOfNodes; i++) {
			if(path[selectedNode][i] >= 0 && selectedNode!= i) { //finding neighbour nodes
				tempLeastCost = leastCostSoFar + path[selectedNode][i] + directPath[i][goalNode];
				if( tempLeastCost < supposedleastCost || supposedleastCost < 0 ) {
					supposedleastCost = tempLeastCost;
					
					supposedSelectedNode = i;
				}
			}
		}
		leastCostSoFar += path[selectedNode][supposedSelectedNode];
		selectedNode = supposedSelectedNode;
		pathToGoal[++top] = selectedNode;
	}
	
	
}
void graph::addEdge(int n, edge e[]) {
    int n1, n2;
    for(int i = 0; i < n; i++) {
        for(int j=0; j<noOfNodes; j++) {
            if( strcmpi( shortNames[j], e[i].start) == 0) {
                n1 = j; break;
            }
        }
        for(int j=0; j<noOfNodes; j++) {
            if( strcmpi( shortNames[j], e[i].end) == 0) {
                n2 = j; break;
            }
        }
        path[n1][n2] = path[n2][n1] = e[i].pathCost;
    }
}

int main() {
   // char* Nodes[2] = new char;
    char* nodes[20][2] = { "Oradea","or", "Zerind","ze", "Arad","ar", "Timisoara","ti",
                    "Lugoj","lu", "Mehadia","me", "Dobreta","do", "Craiova","cr",
                    "Rimnicu Vilcea","ri", "Sibiu","si", "Fagaras","fa", "Pitesti","pi",
                    "Bucharest","bu", "Giurgiu","gi", "Urziceni","ur", "Hirsova","hi",
                    "Eforie","ef", "Vaslui","va", "lasi","la", "Neamt","ne"
        };
    edge e[23] = {   "or", "ze", 230,
                    "ar", "ti", 323
                };

    graph g(20, nodes);
   // g.listNodes();
    g.addEdge(2, e);
	g.setDirectPath("bu", "ar", 366);
	g.setDirectPath("bu", "bu", 366);
	g.setDirectPath("bu", "cr", 160);
	g.setDirectPath("bu", "do", 42);
	g.setDirectPath("bu", "ef", 161);
	g.setDirectPath("bu", "fa", 178);
	g.setDirectPath("bu", "gi", 77);
	g.setDirectPath("bu", "hi", 151);
	g.setDirectPath("bu", "la", 226);
	g.setDirectPath("bu", "lu", 244);
	g.setDirectPath("bu", "me", 241);
	g.setDirectPath("bu", "ne", 234);
	g.setDirectPath("bu", "or", 380);
	g.setDirectPath("bu", "pi", 98);
	g.setDirectPath("bu", "ri", 193);
	g.setDirectPath("bu", "si", 253);
	g.setDirectPath("bu", "ti", 329);
	g.setDirectPath("bu", "ui", 80);
	g.setDirectPath("bu", "va", 199);
	g.setDirectPath("bu", "ze", 374);
    g.findShortestpath("ar", "bu")
    //system("pause");
    return 0;
}

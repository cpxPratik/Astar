#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct edge {
    char* start;
    char* end;
    int pathCost;
   // int directPath;
};

class graph {
private:
    int** path; // two dimensional array works like adjacency matrix of graph but -1 => not adjacent, other value => path cost of edge
    int** directPath; //straight-line distance
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
    void setDirectPath(const char* start, const char* end, int directPathCost);
    void findShortestpath(const char* start, const char* goal);
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
       // delete[] names[i];
//        delete[] shortNames[i];
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

void graph::findShortestpath(const char* start, const char* goal) {
	int startNode, goalNode;
    for(int i=0; i < noOfNodes; i++) {
        if( _strcmpi( shortNames[i], start) == 0) {
			startNode = i; break;
		}
    }
    for(int j=0; j < noOfNodes; j++) {
        if( _strcmpi( shortNames[j], goal) == 0) {
			goalNode = j; break;
		}
    }

	int leastCostSoFar = 0;
	int* pathToGoal = new int[noOfNodes]; // stores routing nodes
	int top = -1;
	pathToGoal[++top] = startNode;
	int selectedNode = startNode; //currently choosen node
	int supposedSelectedNode; // stores node with least estimated cost found so far
	int supposedleastCost = -1; //stores least estimated cost found so far
	int tempLeastCost;
	int count = 0;
	bool alreadyVisitedNode = false;

	while(selectedNode != goalNode) {
		for(int i = 0; i < noOfNodes; i++) {
			alreadyVisitedNode = false;
			for (int j = 0; j <= top; j++) {
				if (i == pathToGoal[j]) {	//makes sure not to return in previous node and prevents infinite loop
					alreadyVisitedNode = true;
					break;
				}
			}
			if(path[selectedNode][i] >= 0 && !alreadyVisitedNode) { //finding neighbour nodes by checking path(edge) cost
				tempLeastCost = leastCostSoFar + path[selectedNode][i] + directPath[i][goalNode];
				if( tempLeastCost < supposedleastCost || supposedleastCost < 0 ) {
					supposedleastCost = tempLeastCost;
					supposedSelectedNode = i;
					//triggerUpdate = true;
				}
			}
		}
        leastCostSoFar += path[selectedNode][supposedSelectedNode]; // adds path cost
        selectedNode = supposedSelectedNode; // chooses new node which as least estimated cost
        pathToGoal[++top] = selectedNode;

		cout << "Choosing \"" << names[pathToGoal[top]] << "\" for minimum estimated cost of " << supposedleastCost << endl;
		supposedleastCost = -1;
		count++;
	}
	cout << endl << "Total looping through while loop or depth of search tree  is "
        << count << endl;
	cout << endl << "Shortest route to " << names[goalNode] << " is through " << endl;
	for(int i = 0; i<= top; i++) {
		cout << names[pathToGoal[i]];
		if(i < top)
            cout <<" -> ";
    }
	cout << endl << endl <<"Total path cost is "<<leastCostSoFar<< endl << endl;
	delete[] pathToGoal;
}

void graph::setDirectPath(const char* start, const char* end, int directPathCost) {
    int n1, n2;
    for(int i=0; i < noOfNodes; i++) {
        if( _strcmpi( shortNames[i], start) == 0) {
            n1 = i; break;
        }
    }
    for(int j=0; j < noOfNodes; j++) {
        if( _strcmpi( shortNames[j], end) == 0) {
            n2 = j; break;
        }
    }
    directPath[n1][n2] = directPath[n2][n1] = directPathCost;
	//cout <<names[n1]<<"   "<<names[n2]<<"   "<<directPathCost<< endl;
}

void graph::addEdge(int n, edge e[]) {
    int n1, n2;
    for(int i = 0; i < n; i++) {
        for(int j=0; j<noOfNodes; j++) {
            if( _strcmpi( shortNames[j], e[i].start) == 0) {
                n1 = j; break;
            }
        }
        for(int j=0; j<noOfNodes; j++) {
            if( _strcmpi( shortNames[j], e[i].end) == 0) {
                n2 = j; break;
            }
        }
        path[n1][n2] = path[n2][n1] = e[i].pathCost;
		//cout <<names[n1]<<"   "<<names[n2]<<"   "<<e[i].pathCost<< endl;
    }
	//cout << endl;
}

int main() {
   // char* Nodes[2] = new char;
    char* nodes[20][2] = { "Oradea","or", "Zerind","ze", "Arad","ar", "Timisoara","ti",
                    "Lugoj","lu", "Mehadia","me", "Dobreta","do", "Craiova","cr",
                    "Rimnicu Vilcea","ri", "Sibiu","si", "Fagaras","fa", "Pitesti","pi",
                    "Bucharest","bu", "Giurgiu","gi", "Urziceni","ur", "Hirsova","hi",
                    "Eforie","ef", "Vaslui","va", "lasi","la", "Neamt","ne"
        };
    edge e[23] = {  "or", "ze", 71,
                    "ze", "ar", 75,
                    "ar", "ti", 118,
                    "ti", "lu", 111,
                    "lu", "me", 70,
                    "me", "do", 75,
                    "do", "cr", 120,
                    "cr", "ri", 146,
                    "ri", "si", 80,
                    "si", "or", 151,
                    "si", "ar", 140,
                    "si", "fa", 99,
                    "fa", "bu", 211,
                    "bu", "pi", 101,
                    "pi", "ri", 97,
                    "pi", "cr", 138,
					"bu", "gi", 90,
                    "bu", "ur", 85,
                    "ur", "hi", 98,
                    "hi", "ef", 86,
                    "ur", "va", 142,
                    "va", "la", 92,
                    "la", "ne", 87
                };

    graph g(20, nodes);
   // g.listNodes();
    g.addEdge(23, e);

	g.setDirectPath("bu", "ar", 366);
	g.setDirectPath("bu", "bu", 0);
	g.setDirectPath("bu", "cr", 160);
	g.setDirectPath("bu", "do", 242);
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
	g.setDirectPath("bu", "ur", 80);
	g.setDirectPath("bu", "va", 199);
	g.setDirectPath("bu", "ze", 374);


	//cout << "
	char initialNode[20];
	bool onNodeList = false;

	cout << "Following are places in Romania and corresponding key :" << endl;
	for (int i = 0; i < 20; i++) {
		cout << setw(14) << nodes[i][0] << " - " << nodes[i][1] << "\t    ";
		if (i % 3 == 0)
			cout << endl;
	}
	do {
		cout << "\nEnter the starting place's key to find shortest route. Bucharest will be destination by default:\n";
		cin >> initialNode;
		for (int i = 0; i < 20; i++) {
			if (_strcmpi(nodes[i][1], initialNode) == 0) {
				onNodeList = true; break;
			}
		}
		if (!onNodeList) {
			cout << "'" << initialNode << "' is not in the above list.\n";
		}
	} while (!onNodeList);
	
	cout << endl;

    g.findShortestpath(initialNode, "bu");
    system("pause");
    return 0;
}

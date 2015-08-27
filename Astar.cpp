#include <iostream>
#include <stdlib.h>
using namespace std;

class graph {
private:
    int **path;
    int **directPath;
    char **names;
    char **shortNames;
    int noOfNodes;
public:
    graph(int noOfNodes, char *names[][2]);
    ~graph();
    bool isConnected(int, int);
    void addEdge(int n1, int n2, int pathcost, int directPathCost);
    void listNodes();
};
void graph::listNodes() {
    for(int i = 0; i < 4; i++){
        cout<<i<<"  "<<names[i]<<" - "<<shortNames[i]<<endl;
    }

}
graph::graph(int no, char *namesArg[][2] ) {
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


int main() {
   // char *Nodes[2] = new char;
    char *nodes[4][2] = { "Oradea","Or", "Zerind", "Ze", "Arad", "Ar", "Timisoara", "Ti" };
    graph g(4, nodes);
    g.listNodes();
    //system("pause");
    return 0;
}

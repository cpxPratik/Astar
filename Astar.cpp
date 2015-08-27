#include <iostream>
#include <stdlib.h>
using namespace std;

class graph {
private:
    int path[4][4];
    int directPath[4][4];
    char *name[4];
    char *shortName[4];
    int n;
public:
    graph(int size, char *names[4][2]);
    ~graph();
    bool isConnected(int, int);
    void addEdge(int, int, int, int);
    void listNodes();
};
void graph::listNodes() {
    for(int i = 0; i < 4; i++){
        cout<<i<<"  "<<name[i]<<" - "<<shortName[i]<<endl;
    }

}
graph::graph(int size, char *names[4][2] ) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            path[i][j] = -1;
        }
        name[i] = names[i][0];
        shortName[i] = names[i][1];
    }
}
graph::~graph() {
}
bool graph::isConnected(int node1, int node2) {
    return (path[node1][node2] >= 0);
}
void graph::addEdge(int n1, int n2, int pathcost, int directPathCost) {
    path[n1-1][n2-1] = path[n2-1][n1-1] = pathcost;
    directPath[n1-1][n2-1] = directPath[n2-1][n1-1] = directPathCost;
}


int main() {
    char *Names[4][2] = { "Oradea","Or", "Zerind", "Ze", "Arad", "Ar", "Timisoara", "Ti" };
    graph g(4, Names);
    g.listNodes();
    //system("pause");
    return 0;
}

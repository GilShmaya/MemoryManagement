#include "../include/Graph.h"
#include "../include/Tree.h"



/** constructors of the Graph class
 * params: gets a matrix that represent an adjacency matrix of the graph*/
 Graph:: Graph(std::vector<std::vector<int>> matrix) : edges(matrix), sickv(),  visited(){
    sickv.resize(matrix.size(), false);
    visited.resize(matrix.size(), false);
 }

/** default constructors of the graph class */
Graph:: Graph(): edges(), sickv(), visited(){}

/** returns the 2D vector of edges */
std::vector<std::vector<int>> Graph:: getEdges() const{
    return edges;
}

/** sets the index in the visited vector of the nodeInd to 'true' */
void Graph:: Visitednode(int nodeInd){
    visited[nodeInd] = true;
}

/** returns a vector of all infected node */
std::vector<int>  Graph:: getInfected() {
    std::vector<int> infected;
    int size = edges.size();
    for(int i=0 ; i < size; i++){
        if(sickv[i])
            infected.push_back(i);
    }
    return infected;
}

/** sets the index in the infected vector of the nodeInd to 'true' */
void Graph:: infectNode(int nodeInd){
    sickv[nodeInd] = true;
    visited[nodeInd] = true;
}

/** return the value of the nodeInd in the infected vector*/
bool Graph:: isInfected(int nodeInd){
    return sickv[nodeInd];
}

/** remove all edges that connect the node to its neighbors*/
void Graph:: removeneighbors(int nodeInd){
    int size = edges.size();
    for(int i=0; i<size; i++) {
        if (i != nodeInd) {
            edges[nodeInd][i] = 0;
            edges[i][nodeInd] = 0;
        }
    }
}

/** return whether all the nodes are infected */
bool Graph:: allinfected(){
    bool ans = true;
    int size = sickv.size();
    for(int i=0 ; i<size && ans ; i++)
        ans = sickv[i];
    return ans;
}

/** return the first neighbors of the node which hasn't been visited yet */
int Graph:: relevantneighbors(int nodeInd){
    int size = edges[nodeInd].size();
    for(int i=0; i < size; i++){
        if (i != nodeInd && edges[nodeInd][i] == 1 && !visited[i]) {
            visited[i] = true;
            return i;
        }
    }
    return -1;
}

/** return the a vector of the node's neighbors */
std::vector<int> Graph:: getNeighbors(int nodeInd){
    std::vector<int> neighbors;
    int size = edges[nodeInd].size();
    for(int i=0 ; i < size; i++){
        if(i != nodeInd && edges[nodeInd][i]==1)
            neighbors.push_back(i);
    }
    return neighbors;
}

/** return a BFS tree that the nodeInd is the root of it */
Tree* Graph:: createBFS(int source, Session& session, Tree* BFStree){
    bool visitedBFS[edges.size()];
    std::queue<Tree*> BFSQ;
    BFSQ.push(BFStree);
    Tree* current;

    //at the beginning we only visited source.
    int size = edges.size();
    for(int i=0; i< size ; i++)
        if(i != source)
            visitedBFS[i] = false;
    visitedBFS[source] = true;

    while(!BFSQ.empty()){
        current = BFSQ.front();
        BFSQ.pop();
        //if the neighbor has not been visited yet - add it to the tree as  child and the visited queue
        for(int neighbor: getNeighbors(current->getNode())){
            if(!visitedBFS[neighbor]){
                visitedBFS[neighbor] = true;
                Tree* child = Tree::createTree(session, neighbor);
                BFSQ.push(child);
                current->addChild(child);
            }
        }
    }

    return BFStree;
}
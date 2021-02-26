#ifndef ASSIGNMENT1_GRAPH_H
#define ASSIGNMENT1_GRAPH_H

#include <vector>
#include <queue>

class Session;
class Tree;

/**
 * @class Graph
 * @brief This class represents a graph, represented using an adjacency matrix. Each node in the graph has an index.
 */

class Graph{
public:
    /** constructors of the graph class */
    Graph(std::vector<std::vector<int>> matrix);

    /** default constructors of the graph class */
    Graph();

    /** returns the 2D vector of edges */
    std::vector<std::vector<int>> getEdges() const;

    /** sets the index in the visited vector of the nodeInd to 'true' */
    void Visitednode(int nodeInd);

    /** returns a vector of all infected node */
    std::vector<int> getInfected();


    /** sets the index in the infected vector of the nodeInd to 'true' */
    void infectNode(int nodeInd);

    /** return the value of the nodeInd in the infected vector*/
    bool isInfected(int nodeInd);

    /** remove all edges that connect the node to its neighbors*/
    void removeneighbors(int nodeInd);

    /** return whether all the nodes are infected */
    bool allinfected();

    /** return the first neighbors of the node which hasn't been visited yet */
    int relevantneighbors(int nodeInd);

    /** return the a vector of the node's neighbors */
    std::vector<int> getNeighbors(int nodeInd);

    /** return a BFS tree that the nodeInd is the root of it */
    Tree* createBFS(int source, Session& session, Tree* BFStree);


private:
    std::vector<std::vector<int>> edges;

    /** indicates for each node whether is sick */
    std::vector<bool> sickv;

    /** indicates for each node whether we already visited there */
    std::vector<bool> visited;

};

#endif
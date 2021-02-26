#ifndef ASSIGNMENT1_SESSION_H
#define ASSIGNMENT1_SESSION_H

#include <iostream>
#include "json.hpp"
#include <queue>
#include <fstream>
#include <vector>
#include <string>
#include "Graph.h"

using json = nlohmann::json;
using namespace std;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:

    /** constructors */
    Session(const std::string &path);

    /** copy constructors */
    Session(const Session& otherSession);

    /** Assignment Operator */
    Session& operator=(const Session& otherSession);

    /** move constructors */
    Session(Session&& otherSession);

    /** move assignment operator */
    Session& operator=(Session&& otherSession);

    /** the destructor of Tree class */
    ~Session();

    /** the simulate() function runs in a loop, until the termination conditions */
    void simulate();

    /** return the agents vector  */
    std::vector<Agent*> getAgents() const;

    /** add new agent to the end of the Agent vector */
    void addAgent(const Agent& agent);

    /** return g */
    Graph& getGraph();

    /** sets the graph*/
    void setGraph(const Graph& graph);

    /** return the Infected Queue  */
    std::queue<int> getInfectedQueue() const;

    /** add new infected node to the end of the infected queue */
    void enqueueInfected(int);

    /** remove and return the last first node in the infected queue */
    int dequeueInfected();

    /** return the type of the graph according the enumeration 'TreeType'  */
    TreeType getTreeType() const;

    /** return the number of cycle the simulate function did so far  */
    int getCycle() const;


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    int cycle;

    /** do deep copy of all the data segment of value */
    void copy(const Session& otherSession);

    /** clear all content session */
    void clear();

    /** steal all data segment of other */
    void steal(Session& otherSession);

    /** The program terminates when each connected component of the graph is either fully infected, or doesn't contain a virus in it.*/
    bool terminated(int size);

    /** create a file named output.json. The file should contain the graph in the last iteration,
     * and a list of infected nodes
     */
    void createoutputfile();

};

#endif
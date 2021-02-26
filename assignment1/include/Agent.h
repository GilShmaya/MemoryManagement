#ifndef ASSIGNMENT1_AGENT_H
#define ASSIGNMENT1_AGENT_H

#include <vector>

// forward declaration
class Session;
class Graph;

/**
 * @class Agent
 * @brief this class describes an Agent in the session
 */
class Agent{
public:

    /** constructors */
    Agent();

    /** the destructor of Agent class */
    virtual ~Agent();

    virtual void act(Session& session)=0;

    /** return a deep copy of the agent */
    virtual Agent* clone() const=0;
};

class ContactTracer: public Agent{
public:

    /** constructors of the ContactTracer class */
    ContactTracer();

    virtual void act(Session& session);

    /** return a deep copy of the agent */
    virtual ContactTracer* clone() const;
};


class Virus: public Agent{
public:

    /** constructors of the Virus class */
    Virus(int nodeInd);

    virtual void act(Session& session);

    /** return the node's index of the virus */
    int getNodeInd() const;

    /** return a deep copy of the agent */
    virtual Virus* clone() const;

private:
    const int nodeInd;
};

#endif
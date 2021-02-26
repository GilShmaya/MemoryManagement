#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"



/*****************************************************************
 * Tree Implementation [Base class]
 ****************************************************************/

/** constructors of the Agent class */
Agent::Agent(){}

/** the destructor of Agent class */
Agent:: ~Agent(){}

/*****************************************************************
 * ContactTracer Implementation
 ****************************************************************/

/** constructors of the ContactTracer class */
ContactTracer::ContactTracer(){}

void ContactTracer::act(Session& session){
    int infectednode = session.dequeueInfected();
    if(infectednode != -1){
        Tree* bfsT = Tree::createTree(session, infectednode);
        bfsT = session.getGraph().createBFS(infectednode, session, bfsT);
        int isolate = bfsT->traceTree();
        session.getGraph().removeneighbors(isolate);
        delete bfsT;
        bfsT = nullptr;
    }
}

/** return a deep copy of the agent */
ContactTracer* ContactTracer:: clone() const{
    return new ContactTracer();
}

/*****************************************************************
 * Virus Implementation
 ****************************************************************/

/** constructors of the Virus class
 * params: gets the index of the virus node in the graph*/
Virus::Virus(int nodeInd): nodeInd(nodeInd){}

/** return the node's index of the virus */
int Virus:: getNodeInd() const{
    return nodeInd;
}

void Virus:: act(Session& session){
    //changes the node of the virus to 'infected'
    if(!session.getGraph().isInfected(nodeInd)){
        session.getGraph().infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    //spreads the virus to the minimum neighbor which hasn't been visited yet - if exist
    int neighbors = session.getGraph().relevantneighbors(nodeInd);
    if(neighbors != -1) {
        Virus a = Virus(neighbors);
        session.addAgent(a);
    }
}


/** return a deep copy of the agent */
Virus* Virus:: clone(Virus&*& v) const{
    return new Virus(*this);
}
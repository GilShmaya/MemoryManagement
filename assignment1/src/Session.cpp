#include "../include/Session.h"
#include "../include/Agent.h"



using json = nlohmann::json;
using namespace std;

/** constructors of the Session class */
Session::Session(const std::string &path): g(), treeType(), agents(), infected(), cycle(0){
    ifstream i(path); //open input stream
    json j;
    i >> j; //read the file and build the json object

    //set the tree type according the config file
    string type = j["tree"];
    if(type == "M")
        treeType = MaxRank;
    else if (type == "C")
        treeType = Cycle;
    else if (type == "R")
        treeType = Root;

    //create the graph according the config file
    g = Graph(j["graph"]);

    //create the agent vector according the config file
    for(auto& element: j["agents"]){
        if(element[0] == "V") {
            agents.push_back(new Virus((int) element[1]));
            //virus can't infect another virus
            g.Visitednode((int) element[1]);
        }
        else
            agents.push_back(new ContactTracer());
    }
}

/** copy constructors of the Session class */
Session:: Session(const Session& otherSession):  g(otherSession.g), treeType(otherSession.treeType), agents(), infected (otherSession.infected) , cycle(otherSession.cycle) {
    for(Agent* agent: otherSession.agents)
        agents.push_back(agent->clone());
}

/** Assignment Operator */
Session& Session:: operator=(const Session& otherSession){
    if(this != &otherSession){
        clear();
        copy(otherSession);
    }
    return *this;
}

/** move constructors */
Session:: Session(Session&& otherSession): g(otherSession.g), treeType(otherSession.treeType), agents(), infected (otherSession.infected) , cycle(otherSession.cycle) {
    for (Agent *agent: otherSession.agents) {
        Agent *a = agent;
        agents.push_back(a);
        agent = nullptr;
    }
    otherSession.agents.clear();
}

/** move assignment operator */
Session& Session:: operator=(Session&& otherSession){
    if(this != &otherSession){
        clear();  // delete the original tree
        steal(otherSession);
    }
    return *this;
}

/** the destructor of Tree class */
Session:: ~Session(){
    clear();
}

/** do deep copy of all the data segment of value */
void Session:: copy(const Session& otherSession){
    g = otherSession.g;
    treeType = otherSession.getTreeType();
    for(Agent* agent: otherSession.agents)
        agents.push_back(agent->clone());
    infected = otherSession.getInfectedQueue();
    cycle = otherSession.getCycle();
}

/** Clear all content */
void Session::clear(){
    int size = agents.size();
    for(int i=0; i < size ; i++){
        if(agents[i] != nullptr){
            delete agents[i];
            agents[i] = nullptr;
        }
    }
    agents.clear();
}

/** steal all data segment of other */
void Session:: steal(Session& otherSession){
    g = otherSession.g;
    treeType = otherSession.getTreeType();
    for(Agent* agent: otherSession.agents){
        Agent* a = agent;
        agents.push_back(a);
        agent = nullptr;
    }
    infected = otherSession.getInfectedQueue();
    cycle = otherSession.getCycle();
    otherSession.agents.clear();
}

/** the simulate() function runs in a loop, until the termination conditions */
void Session:: simulate(){
    cycle = 0;
    int size = 0;
    while(!terminated(size)){
        size = agents.size();
        int i=0;
        while(i<size){
            agents[i]->act(*this);
            i++;
        }
        cycle++;
    }
    createoutputfile(); //save the graph and infected queue in the output file
}

/** return the agents vector  */
std::vector<Agent*> Session:: getAgents() const{
    return agents;
}

/** add new agent to the end of the Agent vector */
void Session:: addAgent(const Agent& agent){
    Agent* clone_agent = agent.clone();
    agents.push_back(clone_agent);
}

/** return the Infected Queue  */
std::queue<int> Session:: getInfectedQueue() const{
    return infected;
}

/** add new infected node to the end of the infected queue */
void Session:: enqueueInfected(int nodeInd){
    infected.push(nodeInd);
}

/** return g */
Graph& Session:: getGraph(){
    return g;
}

/** sets the graph*/
void Session:: setGraph(const Graph& graph){
    g = graph;
}

/** remove and return the last first node in the infected queue */
int Session:: dequeueInfected(){
    if(!infected.empty()){
        int first = infected.front();
        infected.pop();
        return first;
    }
    return -1;
}

/** return the type of the graph according the enumeration 'TreeType'  */
TreeType Session:: getTreeType() const{
    return treeType;
}

/** return the number of cycle the simulate function did so far  */
int Session:: getCycle() const{
    return cycle;
}

/** The program terminates when each connected component of the graph is either fully infected, or doesn't contain a virus in it.*/
bool Session:: terminated(int size){
    int agentssize = agents.size();
    return size==agentssize || g.allinfected();
}

/** create a file named output.json. The file should contain the graph in the last iteration,
* and a list of infected nodes
*/
void Session:: createoutputfile(){
    std::ofstream file("./output.json");
    json output;
    output["graph"] = g.getEdges();
    output["infected"] = g.getInfected();
    file << output;
    file.close();
}

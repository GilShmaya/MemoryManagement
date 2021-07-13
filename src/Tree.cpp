#include "../include/Tree.h"



/*****************************************************************
 * Tree Implementation [Base class]
 ****************************************************************/


/**
 * constructors of the Tree class
 * @param rootLabel
 */
    Tree::Tree(int rootLabel) : node(rootLabel), children(){
}

/**
* the copy contractor of Tree class
* @param t
*/
Tree::Tree(const Tree &otherTree): node(otherTree.node), children(){
    copy(otherTree);
}


/**
* Assignment Operator
*@param otherTree
*/
Tree& Tree::operator=(const Tree &otherTree) {
    //check for "self assignment" and do nothing in that case
    if (this != &otherTree) {
        clear();  // delete the original tree
        copy(otherTree);
    }

    return *this;
}

/**
* move constructor
*@param reference of r-value of otherTree
*/
Tree::Tree(Tree&& otherTree): node(otherTree.getNode()), children(){
    steal(otherTree);
}

/**
* move assignment operator
*@param reference of r-value of otherTree
*/
Tree& Tree::operator=(Tree&& otherTree){
    if(this != &otherTree) {
        clear();  // delete the original tree
        steal(otherTree);
    }
    return *this;
}

/**
* the destructor of Tree class
*/
Tree:: ~Tree(){
    clear();
}

/** do deep copy of all the data segment of value */
void Tree:: copy(const Tree& otherTree){
    node = otherTree.getNode();
    Tree* clone_child;
    int size = otherTree.children.size();
    for (int i =0; i<size; i++){
        clone_child = otherTree.children[i]->clone();
        children.push_back(clone_child);
    }
}

/**
 * Clear all content (delete all childs)
 */
void Tree:: clear(){
    int size = children.size();
    for (int i =0; i<size; i++)
        if(children[i] != nullptr){
            delete children[i];
            children[i] = nullptr;
        }
    children.clear();
}

/** steal all data segment of other */
void Tree:: steal(Tree& otherTree){
    node = otherTree.getNode();
    int size = otherTree.children.size();
    for (int i =0; i< size; i++){
        Tree* child = otherTree.children[i];
        children.push_back(child);
        otherTree.children[i] = nullptr;
    }
    otherTree.children.clear();
}

/**
* return the current node
* @return node
*/
int Tree:: getNode() const {
    return node;
}

/**
* return the current children of the node
* @return children
*/
std::vector<Tree *> Tree::getChildren() const {
    return children;
}

/**
 * add new child to the end of the children vector - right-most child
 * @param child
 */
void Tree:: addChild(const Tree& child){
    Tree* clone_child = child.clone();
    children.push_back(clone_child);
}

/** add new child (by pointer) to the end of the children vector - right-most child */
void Tree:: addChild(Tree* child){
    children.push_back(child);
}

/**
* create a tree with rootLabel as the node and according the type in session
* @param session, rootLable
* @return a pointer to the created tree
 */
Tree* Tree:: createTree(const Session& session, int rootLabel){
    const TreeType type =  session.getTreeType();
    if (type == Cycle)
        return new CycleTree(rootLabel, session.getCycle());
    else if (type == MaxRank)
        return new MaxRankTree(rootLabel);
    else
        return new RootTree(rootLabel);
}

/*****************************************************************
 * CycleTree Implementation
 ****************************************************************/

/**
 * constructors of the CycleTree class
 * @param rootLabel, currCycle
 */
CycleTree:: CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){}

/**
* decide which node to disconnect from the graph.
* @return node to disconnect - the c'th left-most node
*/
int CycleTree:: traceTree(){
    CycleTree* current = this;
    int i = 0;
    while(i < currCycle && !current->getChildren().empty()){
        current = (CycleTree*)(current -> getChildren())[0];
        i++;
    }
    return current -> getNode();
}

/** return a deep copy of the tree */
CycleTree* CycleTree:: clone() const{
    return new CycleTree(*this);
}

/*****************************************************************
 * MaxRankTree Implementation
 ****************************************************************/

/**
 * constructors of the MaxRankTree class
 * @param rootLabel
 */
MaxRankTree:: MaxRankTree(int rootLabel) : Tree(rootLabel){}

/**
* decide which node to disconnect from the graph.
* @return node to disconnect - the node with maximum children
*/
int MaxRankTree:: traceTree(){
    std::queue<MaxRankTree*>  layerqueue;
    layerqueue.push(this);
    MaxRankTree* current;
    int maxnode = getNode();
    int maxchildren = getChildren().size();

    while(!layerqueue.empty()){
        current = layerqueue.front();
        layerqueue.pop();
        int size = current->getChildren().size();
        if(maxchildren < size){
            maxnode = current->getNode();
            maxchildren = size;
        }

        for(Tree* child: current->getChildren()){
            layerqueue.push((MaxRankTree*) child);
        }
    }
    return maxnode;
}

/** return a deep copy of the tree */
MaxRankTree* MaxRankTree:: clone() const{
    return new MaxRankTree(*this);
}

/*****************************************************************
 * RootTree Implementation
 ****************************************************************/

/**
 * constructors of the MaxRankTree class
 * @param rootLabel
 */
RootTree:: RootTree(int rootLabel) : Tree(rootLabel){}

/**
* decide which node to disconnect from the graph.
* @return node to disconnect - the root
*/
int RootTree:: traceTree(){
    return getNode();
}

/** return a deep copy of the tree */
RootTree* RootTree:: clone() const{
    return new RootTree(*this);
}

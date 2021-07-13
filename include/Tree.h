#ifndef ASSIGNMENT1_TREE_H
#define ASSIGNMENT1_TREE_H

#include <vector>
#include <queue>
#include "../include/Session.h"

class Session;

/**
 * @class Tree
 * @brief this class describes a node and its children in a tree and provides some operators on it
 */

class Tree{
public:
    /** constructors of the Tree class */
    Tree(int rootLabel);

    /** the copy contractor of Tree class */
    Tree(const Tree &otherTree);

    /** Assignment Operator */
    Tree& operator=(const Tree &otherTree);

    /** move constructor */
    Tree(Tree&& otherTree);

    /** move assignment operator */
    Tree& operator=(Tree&& otherTree);

    /** the destructor of Tree class */
    virtual ~Tree();

    /** return the current node */
    int getNode() const;

    /** return the current children of the node */
    std::vector<Tree*> getChildren() const;

    /** add new child to the end of the children vector - right-most child  */
    void addChild(const Tree& child);

    /** add new child (by pointer) to the end of the children vector - right-most child */
    void addChild(Tree* child);

    /**
     * create a tree with rootLabel as the node and according the type in session  */
    static Tree* createTree(const Session& session, int rootLabel);

    /** pure virtual function - decide which node to disconnect from the graph */
    virtual int traceTree()=0;

private:
    int node;
    std::vector<Tree*> children;

    /** clear the current tree */
    void clear();

    /** do deep copy of all the data segment of value */
    void copy(const Tree& otherSession);

    /** steal all data segment of other */
    void steal(Tree& otherSession);

    /** return a deep copy of the tree */
    virtual Tree* clone() const=0;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;

    /** return a deep copy of the tree */
    virtual CycleTree* clone() const;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();

private:
    /** return a deep copy of the tree */
    virtual MaxRankTree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();

private:
    /** return a deep copy of the tree */
    virtual RootTree* clone() const override;
};

#endif
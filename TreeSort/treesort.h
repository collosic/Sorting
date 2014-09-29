// Classes for treesort.cpp
#ifndef TREESORT_H  
#define TREESORT_H
#include <algorithm>

class Node {
    // Private variables
    int entry, height, dup_count;
    Node *LeftNodePtr, *RightNodePtr;
    Node *HigherNodePtr;
    bool higher_node_direction;

  public:
    // Constructors
    Node();
    Node(int);
    
    // Class methods
    void setEntry(int a) { entry = a; };
    int getEntry() { return entry; };   
    int getHeight() { return height; };
    int getLeftNodeHeight() { return LeftNodePtr->getHeight(); };
    int getRightNodeHeight() { return RightNodePtr->getHeight(); };
    bool isLeftNodeEmpty() { return LeftNodePtr == 0; };
    bool isRightNodeEmpty() { return RightNodePtr == 0; };
    Node* getLeftNodePtr() { return LeftNodePtr; };
    Node* getRightNodePtr() { return RightNodePtr; };
    void createNewLeftNode(int entry) { LeftNodePtr = new Node(entry); };
    void createNewRightNode(int entry) { RightNodePtr = new Node(entry); };
    void assignNewLeftNode(Node *NewLeftNode) { LeftNodePtr = NewLeftNode; };
    void assignNewRightNode(Node *NewRightNode) { RightNodePtr = NewRightNode; };
    void updateHeightOfNode(int left_h, int right_h) { height = std::max(left_h, right_h) + 1; };
    void setHigherNodePtr(Node *N, bool dir) { HigherNodePtr = N; higher_node_direction = dir; };
    Node* getHigherNodePtr() { return HigherNodePtr; };
    bool getHigherNodeDir() { return higher_node_direction; };
    void incrementDuplicateCount() { dup_count++; };
    int getDupCount() { return dup_count; };
};  

class BinarySearchTree {
    // Private variables 
    Node *RootNode;
    bool is_root_empty;
    
    // Private methods
    void determineEntryPlacement(Node*, int);
    void checkIfUnbalanced(Node*, int, int);
    void balanceTree(Node*, bool);
    void twoRotations(Node*, Node*, bool);
    void rotateAndLink(Node*, bool);
    Node* leftRotation(Node*);
    Node* rightRotation(Node*);
    void ascending(Node*);
    void descending(Node*);
    void determineNewHeight(Node*);
    void determineNewHeight(Node*, int&, int&);
    void checkForDuplicates(Node*);
    void getSubNodeHeights(Node*, int &left, int &right);

  public:
    BinarySearchTree();
    void insertEntry(int);
    int getRootEntry() { return RootNode->getEntry(); };
    void displayTree(bool);
    
};


#endif

// Classes for treesort.cpp
#ifndef TREESORT_H  
#define TREESORT_H
#include <algorithm>

class Node {
    // Private variables
    int entry, height, dup_count;
    Node *LeftNodePtr, *RightNodePtr;

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
    void incrementDuplicateCount() { dup_count++; };
};  

class BinarySearchTree {
    // Private variables 
    Node *RootNode;
    Node *LinkNode;
    bool link_direction;
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
    void assignLinkNode(Node* N) { LinkNode = N; };
    Node* getLinkNode() { return LinkNode; };
    void setLinkDirection(bool t) { link_direction = t; };
    bool getLinkDirection() { return link_direction; };

  public:
    BinarySearchTree();
    void insertEntry(int);
    int getRootEntry() { return RootNode->getEntry(); };
    void displayTree(bool);
    
};


#endif

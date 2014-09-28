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
	void updateHeightOfNode(int l_height, int r_height) { height = std::max(l_height, r_height) + 1; };
	void incrementDuplicateCount() { dup_count++; };
	void checkIfUnbalanced();
};	

class BinarySearchTree {
	// Private variables 
	Node rootNode;
	bool is_root_empty;
	
	// Private methods
	void determineEntryPlacement(Node*, int);
 	 
  public:
	BinarySearchTree() : rootNode() { is_root_empty = true; };
	void insertEntry(int);
	int getRootEntry() { return rootNode.getEntry(); };
};


#endif

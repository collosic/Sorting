// treesort.cpp
#include "treesort.h"

// CONSTANTS
#define EMPTY_NODE_HEIGHT -1


// Constructors and Methods for the Node Class
Node::Node() {
	entry = height = dup_count = 0;
	LeftNodePtr = RightNodePtr = 0;
}
Node::Node(int a) {
	entry = a;
	LeftNodePtr = RightNodePtr = 0;
	height = dup_count = 0;
}


// Constructors and Methods for BinarySearchTree
void BinarySearchTree::insertEntry(int entry) {
	if(is_root_empty) {
		rootNode.setEntry(entry);
		is_root_empty = false;
	} else {
		determineEntryPlacement(&rootNode, entry);
	}
}

void BinarySearchTree::determineEntryPlacement(Node *CurrentNode, int entry) {
	int current_node_entry = CurrentNode->getEntry();

	// Determine if the incoming entry will be placed on the left or right
	// subtree of the current node.
	if(entry < current_node_entry) {
		if(CurrentNode->isLeftNodeEmpty()) {
			CurrentNode->createNewLeftNode(entry);
			//CurrentNode->incrementLeftMax();
		} else {
			determineEntryPlacement(CurrentNode->getLeftNodePtr(), entry);	
			//CurrentNode->incrementLeftMax();
		}	
	} else if(entry > current_node_entry) {
		if(CurrentNode->isRightNodeEmpty()) {
			CurrentNode->createNewRightNode(entry);
			//CurrentNode->incrementRightMax();
		} else {
			determineEntryPlacement(CurrentNode->getRightNodePtr(), entry);
			//CurrentNode->incrementRightMax();				
		}
	} else {
		// This means the current Node entry and the incoming entry 
		// are equal
		CurrentNode->incrementDuplicateCount(); 	
	}
	// Grab the heights of the left and right subtrees.  If a node is empty
	// the height is -1
	int left_height = CurrentNode->isLeftNodeEmpty() ? EMPTY_NODE_HEIGHT 
												: CurrentNode->getLeftNodeHeight();
	int right_height = CurrentNode->isRightNodeEmpty() ? EMPTY_NODE_HEIGHT 
												: CurrentNode->getRightNodeHeight();
	// Update height on current node
	CurrentNode->updateHeightOfNode(left_height, right_height);

	// Call the AVL method to determine if the BST is unbalanced
	//	CurrentNode->checkIfUnbalanced();
}	




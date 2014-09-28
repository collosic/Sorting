// treesort.cpp
#include <iostream>
#include "treesort.h"


// CONSTANTS
#define EMPTY_NODE_HEIGHT -1
#define LINKED_LEFT true
#define LINKED_RIGHT false

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
BinarySearchTree::BinarySearchTree() {
	RootNode = new Node();
	is_root_empty = true;
}

void BinarySearchTree::insertEntry(int entry) {
	if(is_root_empty) {
		RootNode->setEntry(entry);
		is_root_empty = false;
	} else {
		determineEntryPlacement(RootNode, entry);
	}
}

void BinarySearchTree::determineEntryPlacement(Node *CurrentNode, int entry) {
	int current_node_entry = CurrentNode->getEntry();

	// Determine if the incoming entry will be placed on the left or right
	// subtree of the current node.
	if(entry < current_node_entry) {
		if(CurrentNode->isLeftNodeEmpty()) 
			CurrentNode->createNewLeftNode(entry);
		else {
			// Used to link the top Node in a subtree when balancing
			if(CurrentNode->getHeight() == 2) {
				assignLinkNode(CurrentNode);
				setLinkDirection(LINKED_LEFT);
			}
			determineEntryPlacement(CurrentNode->getLeftNodePtr(), entry);	
		}	
	} else if(entry > current_node_entry) { 
		if(CurrentNode->isRightNodeEmpty())  
			CurrentNode->createNewRightNode(entry);
		else {
			if(CurrentNode->getHeight() == 2) {
				assignLinkNode(CurrentNode);
				setLinkDirection(LINKED_RIGHT);
			}
			determineEntryPlacement(CurrentNode->getRightNodePtr(), entry);			
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
	checkIfUnbalanced(CurrentNode, left_height, right_height);
}	

void BinarySearchTree::checkIfUnbalanced(Node *TopNode, int left, int right) {
	int balance_factor = left - right;	
	
	// Left Case
	if(balance_factor >= 2)
		balanceTree(TopNode, LINKED_LEFT);	
	// Right Case
	if(balance_factor <= -2) 
		balanceTree(TopNode, LINKED_RIGHT);
}

void BinarySearchTree::balanceTree(Node *TopNode, bool direction) {
	if(direction == LINKED_LEFT) {
		// Find the height of the left and right subtrees from TopNode's LeftNode
		Node *LeftNode = TopNode->getLeftNodePtr();
		int l_node = LeftNode->getLeftNodePtr() == 0 ? EMPTY_NODE_HEIGHT 
			: LeftNode->getLeftNodeHeight();
		int r_node = LeftNode->getRightNodePtr() == 0 ? EMPTY_NODE_HEIGHT
			: LeftNode-> getRightNodeHeight();
		
		// Calculate balance factor of LeftNode 
		int left_bf = l_node - r_node;

		
	   	if(left_bf == 1) // Left-Left Case
			rotateAndLink(TopNode, LINKED_RIGHT);
		else             // Left-Right Case
			twoRotations(TopNode, LeftNode, LINKED_RIGHT);					
	} else {
		// Opposite of LINKED_LEFT (LINKED_RIGHT)
		Node *RightNode = TopNode->getRightNodePtr();
		int l_node = RightNode->getLeftNodePtr() == 0 ? EMPTY_NODE_HEIGHT 
			: RightNode->getLeftNodeHeight();
		int r_node = RightNode->getRightNodePtr() == 0 ? EMPTY_NODE_HEIGHT 
			: RightNode->getRightNodeHeight();
		
		int right_bf = l_node - r_node;
		
		if(right_bf == -1) 	// Right-Right Case
			rotateAndLink(TopNode, LINKED_LEFT);
		else 				// Right-Left Case
			twoRotations(TopNode, RightNode, LINKED_LEFT);  
	}
}

void BinarySearchTree::twoRotations(Node *TopNode, Node *SubNode, bool direction) {
	if(direction == LINKED_LEFT) {
		// If top node was linked left then rotate to the right 
		// and link to balanced tree
		TopNode->assignNewRightNode(rightRotation(SubNode));
		rotateAndLink(TopNode, LINKED_LEFT);
	} else {
		TopNode->assignNewLeftNode(leftRotation(SubNode));
		rotateAndLink(TopNode, LINKED_RIGHT);
	}
}


void BinarySearchTree::rotateAndLink(Node* TopNode, bool direction) {
	// Link the balanced subtree back to the Binary Search Tree
	if(direction == LINKED_LEFT) {
		if(TopNode == RootNode)
			RootNode = leftRotation(TopNode);
		else {
			Node *TreeNodeLink = getLinkNode();
			if(getLinkDirection() == LINKED_LEFT) 
				TreeNodeLink->assignNewLeftNode(leftRotation(TopNode));
			else
				TreeNodeLink->assignNewRightNode(leftRotation(TopNode));
		}
	} else {
		if(TopNode == RootNode)
			RootNode = rightRotation(TopNode);
		else {
			Node *TreeNodeLink = getLinkNode();
			if(getLinkDirection() == LINKED_LEFT) 
				TreeNodeLink->assignNewLeftNode(rightRotation(TopNode));
			else
				TreeNodeLink->assignNewRightNode(rightRotation(TopNode));
		}
	}
}


Node* BinarySearchTree::rightRotation(Node *OldTopNode) {
	Node *NewTopNode = OldTopNode->getLeftNodePtr();
	OldTopNode->assignNewLeftNode(NewTopNode->getRightNodePtr());
	NewTopNode->assignNewRightNode(OldTopNode);
	return NewTopNode;
}

Node* BinarySearchTree::leftRotation(Node *OldTopNode) {
	Node *NewTopNode = OldTopNode->getRightNodePtr();
	OldTopNode->assignNewRightNode(NewTopNode->getLeftNodePtr());
	NewTopNode->assignNewLeftNode(OldTopNode);
	return NewTopNode;
}

void BinarySearchTree::displayTree(bool ordering) {
	if(ordering) {
		ascending(RootNode);
	} else {
		descending(RootNode);
	}
}

void BinarySearchTree::ascending(Node *Node) {
	if(Node == 0) 
		return;
	ascending(Node->getLeftNodePtr());
	std::cout << Node->getEntry() << "  ";
	ascending(Node->getRightNodePtr());
}

void BinarySearchTree::descending(Node *Node) {
	if(Node == 0) 
		return;
	descending(Node->getRightNodePtr());
	std::cout << Node->getEntry() << "  ";
	descending(Node->getLeftNodePtr());
}


// My implementation of a Binary Seach Tree - treesort.cpp
#include <iostream>
#include "treesort.h"

// CONSTANTS
#define EMPTY_NODE_HEIGHT -1
#define LINKED_LEFT true
#define LINKED_RIGHT false
#define LEFT_EDGE true
#define RIGHT_EDGE false
#define LEFT_HEAVY 2
#define RIGHT_HEAVY -2
#define LEFT_LEFT_CASE 1
#define RIGHT_RIGHT_CASE -1
#define NULL_PTR 0

// Constructors and Methods for the Node Class
Node::Node() {
    entry = height = dup_count = 0;
    LeftNodePtr = RightNodePtr = HigherNodePtr = NULL_PTR;
}
Node::Node(int a) {
    entry = a;
    LeftNodePtr = RightNodePtr = HigherNodePtr = NULL_PTR;
    height = dup_count = 0;
}


// Constructors and Methods for BinarySearchTree.
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
            if(CurrentNode->getHeight() >= 2) {
                // Link the left node with this current node as its 
                // parent node. Used for linking rotated subtrees
                Node *LeftChild = CurrentNode->getLeftNodePtr();
                LeftChild->setHigherNodePtr(CurrentNode, LEFT_EDGE);
            }
            determineEntryPlacement(CurrentNode->getLeftNodePtr(), entry);  
        }   
    } else if(entry > current_node_entry) { 
        if(CurrentNode->isRightNodeEmpty())  
            CurrentNode->createNewRightNode(entry);
        else {
            if(CurrentNode->getHeight() >= 2) {
                Node *RightChild = CurrentNode->getRightNodePtr();
                RightChild->setHigherNodePtr(CurrentNode, RIGHT_EDGE);
            }
            determineEntryPlacement(CurrentNode->getRightNodePtr(), entry);         
        }
    } else {
        // This means the current Node entry and the incoming entry 
        // are equal
        CurrentNode->incrementDuplicateCount();     
    }
    // Get the new height of the current node
    int left_child_height, right_child_height;
    determineNewHeight(CurrentNode, left_child_height, right_child_height);

    // Call the AVL method to determine if the BST is unbalanced
    checkIfUnbalanced(CurrentNode, left_child_height, right_child_height);
}   

void BinarySearchTree::determineNewHeight(Node* CNode) {
    int left_height, right_height;
    getSubNodeHeights(CNode, left_height, right_height);

    // Update height on current node
    CNode->updateHeightOfNode(left_height, right_height);
}

void BinarySearchTree::determineNewHeight(Node* CNode, int &left_height, int &right_height) {
    getSubNodeHeights(CNode, left_height, right_height);

    // Update height on current node
    CNode->updateHeightOfNode(left_height, right_height);
}

void BinarySearchTree::getSubNodeHeights(Node *CNode, int &left, int &right) {
    // Grab the heights of the left and right subtrees.  If a node is empty
    // the height is -1
    left = CNode->isLeftNodeEmpty() ? EMPTY_NODE_HEIGHT 
                                        : CNode->getLeftNodeHeight();
    right = CNode->isRightNodeEmpty() ? EMPTY_NODE_HEIGHT 
                                        : CNode->getRightNodeHeight();
}

void BinarySearchTree::checkIfUnbalanced(Node *TopNode, int left, int right) {
    int balance_factor = left - right;  
    
    // Left Case
    if(balance_factor >= LEFT_HEAVY)
        balanceTree(TopNode, LINKED_LEFT);  
    // Right Case
    if(balance_factor <= RIGHT_HEAVY) 
        balanceTree(TopNode, LINKED_RIGHT);
}

void BinarySearchTree::balanceTree(Node *TopNode, bool direction) {
    if(direction == LINKED_LEFT) {
        // Find the height of the left and right subtrees from TopNode's LeftNode
        Node *LeftNode = TopNode->getLeftNodePtr();
        int l_node, r_node;
        getSubNodeHeights(LeftNode, l_node, r_node);
        
        // Calculate balance factor of LeftNode 
        int left_bf = l_node - r_node;
        
        if(left_bf == LEFT_LEFT_CASE) // Left-Left Case
            rotateAndLink(TopNode, LINKED_RIGHT);
        else             // Left-Right Case
            twoRotations(TopNode, LeftNode, LINKED_RIGHT);                  
    } else {
        // Opposite of LINKED_LEFT (LINKED_RIGHT)
        Node *RightNode = TopNode->getRightNodePtr();
        int l_node, r_node;
        getSubNodeHeights(RightNode, l_node, r_node);
        
        int right_bf = l_node - r_node;
        
        if(right_bf == RIGHT_RIGHT_CASE)  // Right-Right Case
            rotateAndLink(TopNode, LINKED_LEFT);
        else                // Right-Left Case
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
            Node *TreeNodeLink = TopNode->getHigherNodePtr();
            if(TopNode->getHigherNodeDir() == LINKED_LEFT) 
                TreeNodeLink->assignNewLeftNode(leftRotation(TopNode));
            else
                TreeNodeLink->assignNewRightNode(leftRotation(TopNode));
        }
    } else {
        if(TopNode == RootNode)
            RootNode = rightRotation(TopNode);
        else {
            Node *TreeNodeLink = TopNode->getHigherNodePtr();
            if(TopNode->getHigherNodeDir() == LINKED_LEFT) 
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

    // Update heights of rotated Nodes
    determineNewHeight(OldTopNode);
    determineNewHeight(NewTopNode);
    return NewTopNode;
}

Node* BinarySearchTree::leftRotation(Node *OldTopNode) {
    Node *NewTopNode = OldTopNode->getRightNodePtr();
    OldTopNode->assignNewRightNode(NewTopNode->getLeftNodePtr());
    NewTopNode->assignNewLeftNode(OldTopNode);
    
    // Update heights of rotated Nodes
    determineNewHeight(OldTopNode);
    determineNewHeight(NewTopNode);
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
    checkForDuplicates(Node);
    ascending(Node->getRightNodePtr());
}

void BinarySearchTree::descending(Node *Node) {
    if(Node == 0) 
        return;
    descending(Node->getRightNodePtr());
    checkForDuplicates(Node);
    descending(Node->getLeftNodePtr());
}

void BinarySearchTree::checkForDuplicates(Node *Node) {
    int duplicateCount = Node->getDupCount();
    int entry = Node->getEntry();
    if(duplicateCount > 0) {
        for(int i = 0; i < duplicateCount; i++) {
            std::cout << entry << std::endl;
        }
    }
    std::cout << entry << std::endl;
}


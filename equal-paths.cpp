#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int height(Node* root); 
bool equalPathsHelper(Node* root, int cHeight, int height); 


bool equalPaths(Node* root) {
	// calls helper function to ensure that each leaf node is exactly (height) distance away from root
	// cout << "height: " << height(root) << endl; 
    return equalPathsHelper(root, 1, height(root)); 
	
}

int height (Node* root) {
	if(!root) return 0; 
	return 1 + max(height(root->left), height(root->right)); 
}

bool equalPathsHelper(Node* root, int cHeight, int height) {
    if(!root) return true; 

    // checks if root is a leaf node
    if(!root->left && !root->right) {
        // checks if current height of node is equal to height of tree
        if(cHeight == height) return true; 
        return false; 	
    }

    // if root is not a leaf node, recurse to its left and right nodes with cHeight + 1
    return equalPathsHelper(root->left, cHeight + 1, height) && equalPathsHelper(root->right, cHeight + 1, height); 	
}




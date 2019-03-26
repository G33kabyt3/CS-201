
//
//  CatalogTree.c
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include <string.h>
#include "CatalogTree.h"

/*
 * All code below is taken and/or modified from the URL: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * Data Structure is an AVL tree if it wasn't apparent.
 */
// C program to insert a cNode in AVL tree
#include<stdio.h>
#include<stdlib.h>

// A utility function to get maximum of two integers
int maxC(int a, int b);

// A utility function to get the height of the tree
int heightC(struct cNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int maxC(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new cNode with the given key and
 NULL left and right pointers. */
struct cNode* newCNode(struct cNodeData key)
{
    struct cNode* cNode = (struct cNode*)
    malloc(sizeof(struct cNode));
    cNode->key   = key;
    cNode->left   = NULL;
    cNode->right  = NULL;
    cNode->height = 1;  // new cNode is initially added at leaf
    return(cNode);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct cNode *rightRotateC(struct cNode *y)
{
    struct cNode *x = y->left;
    struct cNode *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = maxC(heightC(y->left), heightC(y->right))+1;
    x->height = maxC(heightC(x->left), heightC(x->right))+1;
    
    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct cNode *leftRotateC(struct cNode *x)
{
    struct cNode *y = x->right;
    struct cNode *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = maxC(heightC(x->left), heightC(x->right))+1;
    y->height = maxC(heightC(y->left), heightC(y->right))+1;
    
    // Return new root
    return y;
}

// Get Balance factor of cNode N
int getBalanceC(struct cNode *N)
{
    if (N == NULL)
        return 0;
    return heightC(N->left) - heightC(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with cNode and returns the new root of the subtree.
struct cNode* insertC(struct cNode* cNode, struct cNodeData key)
{
    
    /* 1.  Perform the normal BST insertion */
    if (cNode == NULL)
        return(newCNode(key));
    int priority = strcmp(key.titleP, cNode->key.titleP);
    if ( priority < 0)
        cNode->left  = insertC(cNode->left, key);
    else if (priority > 0)
        cNode->right = insertC(cNode->right, key);
    else // Equal keys are not allowed in BST
        return cNode;
    
    /* 2. Update height of this ancestor cNode */
    cNode->height = 1 + maxC(heightC(cNode->left),
                            heightC(cNode->right));
    
    /* 3. Get the balance factor of this ancestor
     cNode to check whether this cNode became
     unbalanced */
    int balance = getBalanceC(cNode);
    
    // If this cNode becomes unbalanced, then
    // there are 4 cases
    
    // Left Left Case
    if (balance > 1 && strcmp(key.titleP, cNode-> left -> key.titleP)< 0)
        return rightRotateC(cNode);
    
    // Right Right Case
    if (balance < -1 && strcmp(key.titleP, cNode-> right -> key.titleP) > 0)
        return leftRotateC(cNode);
    
    // Left Right Case
    if (balance > 1 &&strcmp(key.titleP, cNode-> left -> key.titleP)> 0)
    {
        cNode->left =  leftRotateC(cNode->left);
        return rightRotateC(cNode);
    }
    
    // Right Left Case
    if (balance < -1 && strcmp(key.titleP, cNode-> right -> key.titleP)< 0)
    {
        cNode->right = rightRotateC(cNode->right);
        return leftRotateC(cNode);
    }
    
    /* return the (unchanged) cNode pointer */
    return cNode;
}


//
//  MovieTree.c
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include <string.h>
#include "MovieTree.h"
#include "CatalogTree.h"


/*
 * All code below is taken and/or modified from the URL: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * Data Structure is an AVL tree if it wasn't apparent.
 */
// C program to insert a mNode in AVL tree
#include<stdio.h>
#include<stdlib.h>

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct mNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new mNode with the given key and
 NULL left and right pointers. */
struct mNode* newmNode(struct mNodeData key)
{
    struct mNode* mNode = (struct mNode*)
    malloc(sizeof(struct mNode));
    mNode->key   = key;
    mNode->left   = NULL;
    mNode->right  = NULL;
    mNode->height = 1;  // new mNode is initially added at leaf
    return(mNode);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct mNode *rightRotate(struct mNode *y)
{
    struct mNode *x = y->left;
    struct mNode *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct mNode *leftRotate(struct mNode *x)
{
    struct mNode *y = x->right;
    struct mNode *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    // Return new root
    return y;
}

// Get Balance factor of mNode N
int getBalance(struct mNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with mNode and returns the new root of the subtree.
struct mNode* insert(struct mNode* mNode, struct mNodeData key)
{
   
    /* 1.  Perform the normal BST insertion */
    if (mNode == NULL)
        return(newmNode(key));
    int priority = strcmp(key.titleP, mNode->key.titleP);
    if ( priority < 0)
        mNode->left  = insert(mNode->left, key);
    else if (priority > 0)
        mNode->right = insert(mNode->right, key);
    else // Equal keys are not allowed in BST
        return mNode;
    
    /* 2. Update height of this ancestor mNode */
    mNode->height = 1 + max(height(mNode->left),
                           height(mNode->right));
    
    /* 3. Get the balance factor of this ancestor
     mNode to check whether this mNode became
     unbalanced */
    int balance = getBalance(mNode);
    
    // If this mNode becomes unbalanced, then
    // there are 4 cases
    
    // Left Left Case
    if (balance > 1 && strcmp(key.titleP, mNode-> left -> key.titleP)< 0)
        return rightRotate(mNode);
    
    // Right Right Case
    if (balance < -1 && strcmp(key.titleP, mNode-> right -> key.titleP) > 0)
        return leftRotate(mNode);
    
    // Left Right Case
    if (balance > 1 &&strcmp(key.titleP, mNode-> left -> key.titleP)> 0)
    {
        mNode->left =  leftRotate(mNode->left);
        return rightRotate(mNode);
    }
    
    // Right Left Case
    if (balance < -1 && strcmp(key.titleP, mNode-> right -> key.titleP)< 0)
    {
        mNode->right = rightRotate(mNode->right);
        return leftRotate(mNode);
    }
    
    /* return the (unchanged) mNode pointer */
    return mNode;
}


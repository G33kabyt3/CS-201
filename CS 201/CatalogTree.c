//
//  CatalogTree.c
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//
#include <string.h>
#include "CatalogTree.h"
#include "MovieTree.h"

/*
 * All code below is taken and/or modified from the URL: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * Data Structure is an AVL tree if it wasn't apparent.
 */
// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
struct Node
{
    struct mNodeData key;
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
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

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
struct Node* newNode(struct mNodeData key)
{
    struct Node* node = (struct Node*)
    malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    
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
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, struct mNodeData key)
{
   int priority = strcmp(key.titleP, node->key.titleP);
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
    
    if ( priority < 0)
        node->left  = insert(node->left, key);
    else if (priority > 0)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
    
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
    
    /* 3. Get the balance factor of this ancestor
     node to check whether this node became
     unbalanced */
    int balance = getBalance(node);
    
    // If this node becomes unbalanced, then
    // there are 4 cases
    
    // Left Left Case
    if (balance > 1 && strcmp(key.titleP, node-> left -> key.titleP)< 0)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && strcmp(key.titleP, node-> right -> key.titleP) > 0)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 &&strcmp(key.titleP, node-> left -> key.titleP)> 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && strcmp(key.titleP, node-> right -> key.titleP)< 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    /* return the (unchanged) node pointer */
    return node;
}


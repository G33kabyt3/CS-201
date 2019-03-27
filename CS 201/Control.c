//
//  Control.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//
// Kinda just merged the database and control classes together
#include "Control.h"
#include "Database.h"


int createUserC(char username [])
{
    return createUser(username);
}

//Wrapper Function for Database PrintUser().
void printUsersC()
{
    printUsers();
}

int deleteUserC()
{
    return 1;
}

//Wrapper function for Database chooseUser().
int logInC(char username [])
{
    return chooseUser(username);
}

void logOutC()
{
    logOutUser();
}

int addToCatalogC()
{
    return 1;
}

int deleteFromCatalogC()
{
    return 1;
}

/*void recursiveDisplay(struct cNode * node)
{
    if(node == NULL)
        return;
    printCNode(*node);
    recursiveDisplay(node->left);
    recursiveDisplay(node->right);
}
void displayCatalogC()
{
    struct cNode* node = getCRoot();
    if(node == NULL)
        return;
    printCNode(*node);
    recursiveDisplay(node->left);
    recursiveDisplay(node->right);
}

*/
/*struct stringLList searchForTitleC()
 {
 return defaultList;
 }
 
 struct stringLList getOptions(char searchTerm[]){
 return defaultList;
 }
 */

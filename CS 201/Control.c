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
//Wrapper for Database deleteUser().
int deleteUserC(char username [50])
{
    return deleteUser(username);
    
}

//Wrapper function for Database chooseUser().
int logInC(char username [])
{
    return chooseUser(username);
}

//Wrapper for Database logOutUser().
void logOutC()
{
    logOutUser();
}

int addToCatalogC(Stack S, int mediaType, char[9] date)
{
    return 1;
}

int deleteFromCatalogC(Stack S)
{
    return 1;
}

int searchMoviesC(char [500] name)
{
    
}

int editCatalog(Stack S)
{
    
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

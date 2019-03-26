//
//  Database.h
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include "MovieTree.h"
#include "CatalogTree.h"
struct mNode* mRoot;
struct cNode* cRoot;
struct MovieList{
    
};



void refreshUsers(void);
void bootDatabase(void);
void closeDatabase(void);
struct mNodeData extractMData(char movieString[]);
struct cNodeData extractCData(char movieString[]);
int sampleFunction(void);
int createUser(char username[50]);
int chooseUser(char username[50]);
int printUsers(void);
#endif /* Database_h */

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
#include "MovieStack.h"

void testPrint(void);
void refreshUsers(void);
void bootDatabase(void);
void closeDatabase(void);
int sampleFunction(void);
int createUser(char username[50]);
int chooseUser(char username[50]);
int deleteUser(char username[50]);
int printUsers(void);
void logOutUser(void);
struct mNode* getMRoot(void);
struct cNode* getCRoot(void);
Stack searchMovies(char * title);
void printM (void *a);
void printC (void *a);

int deleteC(Node n);
int addMovieToCatalog(Node n, int media, char dateArray[9]);

#endif /* Database_h */

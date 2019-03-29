//
//  Control.h
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef Control_h
#define Control_h

#include <stdio.h>

int createUserC(char[]);
int deleteUserC(char username [50]);
void printUsersC(void);
int logInC(char[]);
void logOutC(void);

int addToCatalogC(void);
int deleteFromCatalogC(void);
void displayCatalogC(void);

struct stringLList searchForTitleC(void);



#endif /* Control_h */

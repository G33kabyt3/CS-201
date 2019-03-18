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
#include "UserList.h"

struct MovieList{
    
};



void refreshUsers(void);
void bootDatabase(void);
struct mNodeData extractData(char movieString[]);
int addUser(struct User);
#endif /* Database_h */

//
//  UserList.h
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef UserList_h
#define UserList_h

#include <stdio.h>

struct User {
    char username[100];
    char password [100];
   // struct MovieList catalog;
    struct User * nxtUser;
};

int addUserUL(char [100], char [100]);
#endif /* UserList_h */

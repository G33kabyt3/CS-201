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

struct MovieList{
    
};

struct User {
    char username[100];
    char password [100];
    struct MovieList catalog;
    struct User * nxtUser;
};

int addUser(struct User);
void refreshUsers(void);

#endif /* Database_h */

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

struct mNodeData
{
    //Database ID of the title.
    int ID;
    //Type of title.
    char type [20];
    //The primary title.
    //Assuming titles won't run past 200 characters...
    char titleP[200];
    //Original title.
    char titleO[200];
    //0 for isn't, 1 for is.
    int isAdult;
    //Year the title started.
    int startYear;
    //Year the title ended.
    int endYear;
    //Runtime in minutes.
    int runtime;
    //Genre of the title.
    char genre [40];
};

int addUser(struct User);
void refreshUsers(void);
void bootDatabase(void);
struct mNodeData extractData(char movieString[]);

#endif /* Database_h */

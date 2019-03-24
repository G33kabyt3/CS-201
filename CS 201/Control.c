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
#include "UserList.h"
struct User* topUser;
struct User* currentUser = NULL;
struct stringLList defaultList;



int createUserC(char username [], char password[])
{
    int success;
    struct User tempUser = {
        *username, *password
    };
  success = addUser(tempUser);
    return success;
}



int deleteUserC()
{
    return 1;
}

int logInC(char username [], char password[])

{
    return 1;
}

void logOutC()
{
    currentUser = NULL;
}

int addToCatalogC()
{
    return 1;
}

int deleteFromCatalogC()
{
    return 1;
}

struct stringLList displayCatalogC()
{
    return defaultList;
}

struct stringLList searchForTitleC()
{
    return defaultList;
}

struct stringLList getOptions(char searchTerm[]){
    return defaultList;
}

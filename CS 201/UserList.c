//
//  UserList.c
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//
#include <string.h>
#include "UserList.h"


struct User * firstUser;
int addUserUL(char username [100], char password [100])
{
struct User newUser;
   struct User * dummy = firstUser;
    int isBefore;
    if (dummy == NULL)
    {
        firstUser = &newUser;
        return 1;
    } else {
        while (dummy->nxtUser != NULL)
        {
            isBefore = strcmp(newUser.username, dummy ->nxtUser->username);
           if ( isBefore < 0)
           {
               newUser.nxtUser = dummy-> nxtUser;
               dummy->nxtUser = &newUser;
               return 1;
           } else if (isBefore == 0)
           {
               return 0;
           } else {
               dummy = dummy -> nxtUser;
           }
        }
        dummy ->nxtUser = &newUser;
        return 1;
    }
}

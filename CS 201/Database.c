//
//  Database.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include "Database.h"

int addUser(struct User user)
{
    return 1;
}

void refreshUsers ()
{
    FILE* userFile;
    userFile = fopen("userinfo.txt", "f");
    if (!userFile)
    {
        printf("File not found. Creating new file.\n");
        fopen("userinfo.txt", "w")
    } else {
        printf("User file found!\n");
    }
    
}

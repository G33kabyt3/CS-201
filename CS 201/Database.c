//
//  Database.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include "Database.h"
#include <sys/stat.h>
#include <sys/types.h>

int addUser(struct User user)
{
    return 1;
}

void refreshUsers ()
{
    FILE* userFile;
    int success = mkdir("201Data", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    userFile = fopen("201Data/userData.txt", "w+");
    fclose(userFile);
}

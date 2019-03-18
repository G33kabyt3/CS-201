//
//  Database.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "MovieTree.h"
#include "UserList.h"
FILE* userFile;
FILE* movieFile;



int addUser(struct User user)
{
    return 1;
}

void refreshUsers ()
{
    
    
}
struct mNodeData extractData(char movieString [] )
{
    
    //Database ID of the title.
    struct mNodeData temp;
    char delim = '\t';
    int j=0;
    long entryLength = strlen(movieString);
    //Using a for loop to tell what part of the entry we are on.
    for (int i = 0; i < 9; i++ )
    {
        char token [entryLength];
        int sep =0;
        while (j < entryLength && movieString[j] != delim)
        {
            token[sep] = movieString[j];
            j++;
            sep++;
        }
        token [sep] = '\0';
        j++;
        printf("%s", token);
        switch (i){
            case 0: temp.ID = atoi (token);
                break;
            case 1: strcpy(temp.type, token);
                break;
            case 2: strcpy(temp.titleP, token);
                break;
            case 3: strcpy(temp.titleO, token);
                break;
            case 4: temp.isAdult = atoi (token);
                break;
            case 5: temp.startYear = atoi(token);
                break;
            case 6: temp.endYear = atoi (token);
                break;
            case 7: temp.runtime = atoi (token);
                break;
            case 8: strcpy(temp.genre, token);
                break;
        }
    }
    
    
    return temp;
}

void bootDatabase()
{
    mkdir("201Data", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    userFile = fopen("201Data/userData.txt", "w+");
    movieFile = fopen("201Data/data.tsv", "r");
}
void databaseShutdown()
{
    fclose(userFile);
    fclose(movieFile);
}

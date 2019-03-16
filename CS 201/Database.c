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
FILE* userFile;
FILE* movieFile;
struct mNodeData
{
    //Database ID of the title.
    int ID;
    //Type of title.
    char * type[20];
    //The primary title.
    //Assuming titles won't run past 200 characters...
    char * titleP [200];
    //Original title.
    char * titleO [200];
    //0 for isn't, 1 for is.
    int isAdult;
    //Year the title started.
    int startYear;
    //Year the title ended.
    int endYear;
    //Runtime in minutes.
    int runtime;
    //Genre of the title.
    char * genre [40];
};

struct mNode {
    //Attributes for AVL tree.
    struct mNode * left;
    struct mNode * right;
    int weight;
    struct mNodeData *data;
};



struct  mNode topNode;
struct  User firstUser;

int addUser(struct User user)
{
    return 1;
}

void refreshUsers ()
{
    
    
}
struct mNodeData extractData(char * movieString)
{
    
    //Database ID of the title.
    int ID = -1 ;
    //Type of title.
    char type [20];
    //The primary title.
    char titleP [200];
    //Original title.
    char  titleO [200];
    //0 for isn't, 1 for is.
    int isAdult =-1;
    //Year the title started.
    int startYear = -1;
    //Year the title ended.
    int endYear = -1;
    //Runtime in minutes.
    int runtime =-1;
    //Genre of the title.
    char genre[40];
    
    char * token;
    token = strtok(movieString, "\t");
    //Using a for loop to tell what part of the entry we are on.
    for (int i = 0; i < 10; i++ )
    {
        token = strtok(NULL, "\t");
        
        switch (i){
    case 1: ID = atoi (token);
    case 2: strcpy(type, token);
    case 3: strcpy(titleP, token);
    case 4: strcpy(titleO, token);
    case 5: isAdult = atoi (token);
    case 6: startYear = atoi(token);
    case 7: endYear = atoi (token);
    case 8: runtime = atoi (token);
    case 9: strcpy(genre, token);
        }
    }
    struct mNodeData temp = { ID, type, titleP, titleO, isAdult, startYear, endYear, runtime, genre };
    
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

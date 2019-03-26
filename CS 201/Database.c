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
#include <fcntl.h>
#include "MovieTree.h"
#include "UserTree.h"
#include <dirent.h>
FILE* userFile;
FILE* movieFile;
struct mNode* mRoot;
struct UNode* uRoot;


void refreshUsers ()
{
    
    
}
/*
 * Creation, selections, printing of users.
 *
 */

// Takes a username, creates a file for it.
int createUser(char username[50])
{
    //Path shouldn't be more than 75 due to the fact the functions take an array of size 50.
    char path [75] = "UserData/";
    strcat(path, username);
    strcat(path, ".log");
    userFile = fopen(path, "r");
    if (userFile != NULL)
    {
        printf("User already exists!\n");
        return 0;
    }
    userFile = fopen(path, "w+");
    if (userFile == NULL)
    {
        printf("User file not found!\n");
        return 0;
    }
    return 1;
}

// Takes a username, sets the current user file to that user.
int chooseUser(char username[50])
{
    char path [75] = "UserData/";
    strcat(path, username);
    strcat(path, ".log");
    userFile = fopen(path, "r+");
    if (userFile == NULL)
    {
        printf("User file not found!\n");
        return 0;
    }
    return 1;
}

int printUsers ()
{
    struct dirent *subdir;
    DIR *dir;
    dir = opendir("./UserData");
    if (dir)
    {
        subdir = readdir(dir);
        subdir = readdir(dir);
        while ((subdir = readdir(dir)) != NULL)
        {
            printf("%s\n", subdir->d_name);
        }
        closedir(dir);
    }
    return(0);
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
        switch (i){
            case 0:
                memmove(&token[0], &token[1], strlen(token));
                memmove(&token[0], &token[1], strlen(token));
                printf("%s ", token);
                temp.ID = atoi (token);
                break;
                case 1: strcpy(temp.type, token);
                printf("%s ", token);
                break;
            case 2: strcpy(temp.titleP, token);
                printf("%s ", token);
                break;
            case 3: strcpy(temp.titleO, token);
                printf("%s ", token);
                break;
            case 4: temp.isAdult = atoi (token);
                printf("%s ", token);
                break;
            case 5: temp.startYear = atoi(token);
                printf("%s ", token);
                break;
            case 6: temp.endYear = atoi (token);
                printf("%s ", token);
                break;
            case 7: temp.runtime = atoi (token);
                printf("%s ", token);
                break;
            case 8: strcpy(temp.genre, token);
                printf("%s\n", token);
                break;
        }
    }
    
    
    return temp;
}



void refreshDatabase()
{
    // Max length of file line to read.
    int maxLength = 500;
    // Temporary string variable.
    char curLine [maxLength];
    while (fgets(curLine, maxLength, movieFile) != NULL)
    {
         mRoot = insert(mRoot, extractData(curLine));
    }
    
    while (fgets(curLine, maxLength, userFile))
    {
        
    }
}

void bootDatabase()
{
    //TODO: Make better file pathnames.
    mkdir("MovieData", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("UserData", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   
    movieFile = fopen("/Users/Theepicone1/Documents/MovieInfo.txt", "r");
    if (movieFile == NULL)
    {
        printf("Movie file not found!\n");
    }
    //TO_DO: Uncomment.
    //refreshDatabase();
}
void closeDatabase()
{
    fclose(userFile);
    fclose(movieFile);
}

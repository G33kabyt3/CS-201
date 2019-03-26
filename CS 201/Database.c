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
#include "CatalogTree.h"
#include <dirent.h>
FILE* userFile;
FILE* movieFile;



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






/*
 *
 * Extractions classes. They take a string, turn it into the appropriate data struct. They take advantage of how the data is formated to know what data
 * will end up where and how far it needs to read.
 *
 */
struct mNodeData extractMData(char movieString [] )
{
    
    struct mNodeData temp;
    char delim = '\t';
    int j=0;
    long entryLength = strlen(movieString);
    //Using a for loop to keep track of what part of the entry we are on.
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


struct cNodeData extractCData(char movieString [] )
{
    
    struct cNodeData temp;
    char delim = '\t';
    int j=0;
    long entryLength = strlen(movieString);
    //Using a for loop to keep track of what part of the entry we are on.
    for (int i = 0; i < 11; i++ )
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
            case 9:
                temp.mediaType = atoi(token);
                break;
            case 10:
                strcpy(temp.date, token);
                break;
        }
    }
    
    
    return temp;
}

//Converting a node's data into a line of data in the user file and adding it to memory.
int addMovieToCatalog(struct cNodeData data)
{
    if (userFile == NULL)
    {
        return 0;
    }
    
    //add to user file.
    fprintf(userFile, "%i\t", data.ID);
    fprintf(userFile, "%s\t" , data.type);
    fprintf(userFile, "%s\t" , data.titleP);
    fprintf(userFile,"%s\t" , data.titleO);
    fprintf(userFile,"%i\t" , data.isAdult);
    fprintf(userFile,"%i\t" , data.startYear);
    fprintf(userFile,"%i\t" , data.endYear);
    fprintf(userFile,"%i\t" , data.runtime);
    fprintf(userFile,"%s\t" , data.genre);
    fprintf(userFile,"%i\t" , data.mediaType);
    fprintf(userFile,"%s\n" , data.date);
    
    //Load into memory.
    cRoot = insertC(cRoot, data);
    return 1;
}

void loadMovies()
{
    // Max length of file line to read.
    int maxLength = 500;
    // Temporary string variable.
    char curLine [maxLength];
    while (fgets(curLine, maxLength, movieFile) != NULL)
    {
         mRoot = insert(mRoot, extractMData(curLine));
    }
    
    
}


//Loads current user's whole catalog into memory.
void loadCatalog()
{
    // Max length of file line to read.
    int maxLength = 550;
    // Temporary string variable.
    char curLine [maxLength];
    while (fgets(curLine, maxLength, userFile))
    {
        cRoot = insertC(cRoot, extractCData(curLine));
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
    //loadMovies();
}
void closeDatabase()
{
    fclose(userFile);
    fclose(movieFile);
}

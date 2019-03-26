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
#include "CatalogTree.h"
struct User* topUser;
struct User* currentUser = NULL;
struct stringLList defaultList;



/*int createUserC(char username [], char password[])
{
    int success;
    struct User tempUser = {
        *username, *password
    };
  success = addUser(tempUser);
    return success;
}
 */



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
void printCNode(struct cNode node)
{
    //Print out basic movie data.
    printf("%i \t" , node.key.ID);
    printf("%s \t" , node.key.type);
    printf("%s \t" , node.key.titleP);
    printf("%s \t" , node.key.titleO);
    printf("%i \t" , node.key.isAdult);
    printf("%i \t" , node.key.startYear);
    printf("%i \t" , node.key.endYear);
    printf("%i \t" , node.key.runtime);
    printf("%s \t" , node.key.genre);
   //Print out media type
    switch (node.key.mediaType)
    {
        case 0:
            printf("Digital\t");
            break;
        case 1:
            printf("DVD\t");
            break;
        case 2:
            printf("BluRay\t");
    }
    printf("%c" , node.key.date[0]);
    printf("%c" , node.key.date[1]);
    printf("/");
    printf("%c" , node.key.date[2]);
    printf("%c" , node.key.date[3]);
    printf("/");
    printf("%c", node.key.date[4]);
    printf("%c", node.key.date[5]);
    printf("%c", node.key.date[6]);
    printf("%c", node.key.date[7]);
    
    
 
    
    
    
}
void displayCatalogC()
{
    
}

struct stringLList searchForTitleC()
{
    return defaultList;
}

struct stringLList getOptions(char searchTerm[]){
    return defaultList;
}

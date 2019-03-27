//
//  Interface201.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interface201.h"
#include "Control.h"

/*
 *
 * User Functions
 *
 */

void createUserI()
{
    
    
    char username[20];
    int success =0;
    while (success!= 1)
    {
        printf("Please type the desired username for the new user. Please note that it may only be 20 characters long. Any overflow characters will not be considered.\n");
        scanf("%20s", username);
        success = createUserC(username);
        if (success == 0)
        {
            printf("Username taken. Please try another.\n");
        }
        
    }
    printf("Creation Successful. \n");
}

int logInI()
{
    char username[20];
    printf("Printing user files...\n");
    printUsersI();
    printf("Please type in the name of the user file you wish to access (Just the name, not the .log).\n");
    scanf("%20s", username);
    if (logInC(username)==0)
    {
        printf("Incorrect log in information. Please try again later.\n");
        return 0;
    }
    return 1;
    
}

void logOutI()
{
    logOutC();
    printf("Logout successful.\n");
}

void deleteUserI()
{
    deleteUserC();
    printf("Delete successful.\n");
}

//Wrapper for control print users.
void printUsersI(){
    printUsersC();
}


/*
 *
 * Catalog Functions
 *
 */
void addToCatalogI()
{
    
}

void deleteFromCatalogI()
{
    
}

//Displays all movies in the catalog. Must have catalog loaded into memory first.
void displayCatalogI()
{
    //displayCatalogC();
}

void searchForTitleI()
{
    
}


/*
 *
 * Main Menus
 *
 */

void mainMenu()
{
    unsigned long numBytes = 10;
    char *str;
    str = (char *) malloc (numBytes+1);
    int terminate =1;
    while ( terminate != 0){
        printf("Hello! Type 0 to search for a title, 1 to add a your catalog, 2 to delete from your catalog, 3 to display your catalog, 4 to log out, and 5 to delete the current user.\n ");
        getline(&str, &numBytes, stdin);
        if (strcmp(str, "0\n") == 0)
        {
            printf("Search For Title Selected.\n");
            searchForTitleI();
        } else if (strcmp(str, "1\n") == 0)
        {
            printf("Add to Catalog Collected.\n");
            addToCatalogI();
        } else if (strcmp(str, "2\n") ==0 ){
            printf("Delete From Catalog Selected.\n");
            deleteFromCatalogI();
        } else if (strcmp(str, "3\n") == 0)
        {
            printf("Display Catalog Selected.\n");
            displayCatalogI();
        } else if (strcmp(str, "4\n") == 0)
        {
            printf("Log Out Selected\n");
            logOutI();
            terminate = 0;
            
        } else if (strcmp(str, "5\n") == 0)
        {
            printf("Delete Current User Selected.\n");
            deleteUserI();
            terminate = 0;
        } else {
            printf("Please provide valid input.\n");
        }
    }
    free(str);
}

void bootInterface()
{
    unsigned long numBytes = 10;
    char *str;
    str = (char *) malloc (numBytes+1);
    int exit =1;
    char exitCode[] = "$exit\n";
    while ( exit != 0)
    {
        printf("Hello! Type 0 to Log In, 1 to Create a User, and $exit to exit. \n ");
        getline(&str, &numBytes, stdin);
        if (strcmp(str, "0\n") == 0)
        {
            printf("Log In Selected.\n");
            
            if (logInI() == 1)
            {
                printf("Log in Successful! Sending to Main Menu.\n");
                mainMenu();
            }
            
        } else if (strcmp(str, "1\n") == 0)
        {
            printf("Create User Selected.\n");
            createUserI();
        } else if ( strcmp(str, exitCode) == 0)
        {
            exit = 0;
        } else {
            printf("Please provide valid input.\n");
        }
        
    }
    free (str);
}

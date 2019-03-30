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
 * A username can be 50 characters long. Any extra characters will not be considered.
 *
 */

//
void createUserI()
{
    
    
    char username[51];
    int success =0;
    while (success!= 1)
    {
        printf("Please type the desired username for the new user. Please note that it may only be 50 characters long. Any overflow characters will not be considered.\n");
        scanf("%50s", username);
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
    char username[51];
    printf("Printing user files...\n");
    printUsersI();
    printf("Please type in the name of the user file you wish to access (Just the name, not the .log).\n");
    scanf("%50s", username);
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
    char username[51];
    int success =0;
    while (success!= 1)
    {
        printf("Please type the username for the user you wish to delete . Please note that it may only be 50 characters long. Any overflow characters will not be considered.\n");
        scanf("%50s", username);
        success = createUserC(username);
        if (success == 0)
        {
            printf("Username taken. Please try another.\n");
        }
        
    }
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
    char title[201];
    int success =0;
    while (success!= 1)
    {
        printf("Please type the name of the movie you wish to Add . Please note that the title may only be 200 characters long. Any overflow characters will not be considered.\n");
        scanf("%200s", title);
        printf("Printing out results.../n");
        Stack results =searchMoviesC(title);
        if (Peek(results)==NULL)
        {
            printf("No results found. Please try again with a different query.\n");
            return;
        }
        int numElements = printStackM(results);
        unsigned long int choice = 0;
        while (choice == 0){
            printf("Type the number of the result you wish to add. Any digits beyond the 7th will not be considered.\n");
            char digits [8];
            scanf("%7s", digits);
            choice =  strtoul(digits, (char **)NULL, 10);
            if (choice == 0)
            {
                printf("Please type in a non-zero number\n");
            } else if (choice >numElements)
            {
                choice =0;
                printf("Please choose a listed option.\n");
            }
        }
        int readMedia =0;
        unsigned long int input =0;
        char digits [2];
        while (input == 0){
            printf("Please type in a the format of your addition. Type 1 for digital, 2 for DVD, and 3 for Blu-Ray.\n");
            scanf("%1s", digits);
            input =  strtoul(digits, (char **)NULL, 10);
            if (readMedia == 0)
            {
                printf("Please type in a non-zero number\n");
            } else if (input >2 )
            {
                input =0;
                printf("Please choose a listed option");
            } else {
                //We can safely cast now that we know the input is within our cases.
                readMedia = (int) input;
            }
        }
        // If I was coding in a different langugue and had libraries available to me I might actually bother forcing a date format on the user.
        // However, there really doesn't seem to be a way to do this from scratch in C without it being a LOT more effort than it's worth.
        // So I won't.
        char date [18];
        printf("Please type in the date acquired. Use any format you want, but you're capped at 17 characters.\n");
        scanf("%17s", date);
        addToCatalogC(results, readMedia, date, choice);
    }
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
            //What happens if current user is deleted?
            printf("Delete User Selected.\n");
            deleteUserI();
            
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
